from socket import *
import json

import xor
from rsa import *


class Connection:
    def __init__(self, ip: str, port: int, email: str, password: str):
        self.socket = socket(AF_INET, SOCK_STREAM)
        self.socket.setsockopt(IPPROTO_TCP, TCP_NODELAY, 1)
        self.socket.connect((ip, port))

        self.rsa = RSA(32)
        jsn = json.loads(self.recv_bytes().decode('utf-8'))

        self.rsa.number_n = int(jsn["n"])
        self.rsa.number_e = int(jsn["e"])

        self.xor_key = xor.GenerateKey(256)
        enc_key = self.rsa.Encrypt(self.xor_key)

        self.socket.send(len(enc_key).to_bytes(4, byteorder='little'))
        self.socket.sendall(enc_key)

        self.__user = User(self, self.send_json_enc({"route": "/auth",
                                                     "email": email,
                                                     "password": password})["user_id"])

    def __del__(self):
        self.socket.close()

    def get_logged_user(self):
        return self.__user

    def send_json(self, jsn: dict) -> dict:
        data = bytes(json.dumps(jsn), 'utf-8')
        self.socket.send(len(data).to_bytes(4, byteorder='little'))

        self.socket.sendall(data)

        return json.loads(self.recv_bytes().decode('utf-8'))

    def recv_bytes(self) -> bytes:
        size = int.from_bytes(self.socket.recv(4), byteorder='little')
        return self.socket.recv(size)

    def send_json_enc(self, jsn: dict) -> dict:
        data = xor.Encrypt(list(bytes(json.dumps(jsn), 'utf-8')), self.xor_key)
        self.socket.send(len(data).to_bytes(4, byteorder='little'))

        self.socket.sendall(data)
        return json.loads(xor.Encrypt(list(self.recv_bytes()), self.xor_key).decode('utf-8'))


class User:
    def __init__(self, con: Connection, id: int):
        self.connection = con
        self.id = id

    def get_name(self) -> str:
        data = self.connection.send_json_enc({"route": "/user/get/name", "id": self.id})
        return data["name"]

    def get_status(self) -> str:
        data = self.connection.send_json_enc({"route": "/user/get/status", "id": self.id})
        return data["status"]

    def set_name(self, name: str) -> None:
        self.connection.send_json_enc({"route": "/user/set/name", "id": self.id, "name": name})

    def set_status(self, status: str) -> None:
        self.connection.send_json_enc({"route": "/user/set/status", "id": self.id, "status": status})

    def get_chats(self):
        chats = []

        data = self.connection.send_json_enc({"route": "/user/get/chat_list", "id": self.id})["chats"]
        for chatJson in data:
            chats.append(Chat(self.connection, chatJson["id"]))

        return chats

    def get_configs(self):
        data = self.connection.send_json_enc({"route": "/user/get/configs", "id": self.id})['configs']
        return [Config(self.connection, x["id"]) for x in data]


class Chat:
    def __init__(self, con: Connection, id: int):
        self.connection = con
        self.id = id

    def get_name(self) -> str:
        data = self.connection.send_json_enc({"route": "/chat/get/name", "id": self.id})
        return data["name"]

    def get_invite(self) -> str:
        data = self.connection.send_json_enc({"route": "/chat/get/invite", "id": self.id})
        return data["invite"]

    def get_history(self):
        data = self.connection.send_json_enc({"route": "/chat/get/history", "id": self.id})
        return [Message(self.connection, jsn["id"]) for jsn in data["messages"]]

    def send_message(self, text: str):
        self.connection.send_json_enc({"route": "/chat/send/message", "id": self.id, "message": text})


class Message:
    def __init__(self, con: Connection, id: int):
        self.connection = con
        self.id = id

    def get_text(self):
        return self.connection.send_json_enc({"route": "/chat/message/text", "id": self.id})['text']

    def get_owner(self):
        id: int = self.connection.send_json_enc({"route": "/chat/message/owner", "id": self.id})['id']

        return User(self.connection, id)


class Config:
    def __init__(self, con: Connection, id: int):
        self.connection = con
        self.id = id

    def get_data(self):
        print(self.connection.send_json_enc({"route": "/config/get/data", "id": self.id}))
        return self.connection.send_json_enc({"route": "/config/get/data", "id": self.id})["data"]
