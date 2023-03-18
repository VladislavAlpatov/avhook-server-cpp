from socket import *
import json

soc = socket(AF_INET, SOCK_STREAM)
soc.connect(("192.168.111.128", 7777))


def req(sct: socket, jsn):
    data = bytes(json.dumps(jsn), 'utf-8')
    sct.send(len(data).to_bytes(4, byteorder='little'))

    sct.sendall(data)
    sct.recv(4)
    return sct.recv(1024).decode('utf-8')


data = req(soc, {"route": "/auth",
                 "email": "1@mail.ru",
                 "password": "1235"})
print(data)


class User:
    def __init__(self, id: int):
        self.id = id

    def GetName(self) -> str:
        data = req(soc, {"route": "/user/get/name", "id": self.id})
        return json.loads(data)["name"]

    def GetStatus(self) -> str:
        data = req(soc, {"type": 2, "id": self.id})
        return json.loads(data)["status"]

    def SetName(self, name: str) -> None:
        data = req(soc, {"/user/set/name": 4, "id": self.id, "name": name})


usr = User(2)
usr.SetName("vlad")
print(usr.GetName())
