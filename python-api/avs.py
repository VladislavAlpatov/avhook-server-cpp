from socket import *
import json

print("started")
soc = socket(AF_INET, SOCK_STREAM)
soc.connect(("127.0.0.1", 7777))


def req(sct: socket, jsn):
    data = bytes(json.dumps(jsn), 'utf-8')
    sct.send(len(data).to_bytes(4, byteorder='little'))

    sct.sendall(data)
    sct.recv(4)
    return sct.recv(1024).decode('utf-8')


req(soc, {"type": 5, "email": "1@mail.ru", "password": "1235"})


class User:
    def __init__(self, id: int):
        self.id = id

    def GetName(self) -> str:
        data = req(soc, {"type": 1, "id": self.id})

        return json.loads(data)["name"]

    def GetStatus(self) -> str:
        data = req(soc, {"type": 2, "id": self.id})

        return json.loads(data)["status"]


usr = User(1)

print(f"My username is '{usr.GetName()}', and my status is `{usr.GetStatus()}`")
