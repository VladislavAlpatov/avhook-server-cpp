from socket import *
import json


class Connection:
    def __init__(self, ip: str, port: int, email: str, password: str):
        self.socket = socket(AF_INET, SOCK_STREAM)
        self.socket.connect((ip, port))

        self.__user = User(self, self.send_json({"route": "/auth",
                                                 "email": email,
                                                 "password": password})["user_id"])

    def get_logged_user(self):
        return self.__user

    def send_json(self, jsn: dict) -> dict:
        data = bytes(json.dumps(jsn), 'utf-8')
        self.socket.send(len(data).to_bytes(4, byteorder='little'))

        self.socket.sendall(data)
        self.socket.recv(4)

        return json.loads(self.socket.recv(1024).decode('utf-8'))


class User:
    def __init__(self, con: Connection, id: int):
        self.connection = con
        self.id = id

    def get_name(self):
        data = self.connection.send_json({"route": "/user/get/name", "id": self.id})
        return data["name"]

    def get_status(self):
        data = self.connection.send_json({"route": "/user/get/status", "id": self.id})
        return data["status"]

    def set_name(self, name: str):
        self.connection.send_json({"route": "/user/set/name", "id": self.id, "name": name})