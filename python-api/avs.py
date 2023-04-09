from socket import *
import json


n = 16843339067530518453439786011894685916079692885081421598202755475296839151101645543868856708401821131090978684913453383557474011021068374288205217611652394035039621815205974345135349672375931212406541170147624500664560957635865358415178710845275010767807477031530815469854865003291971977566049714398909418262421190001725285564808156916366423069077094190535098510760025096331317487306432543174890202853794481168871900498154345684757022496399681776942969502783331389702806383892393103520397656565385853356770743156992172830157468635295539199895846880438221247281265670866302912976438905779427492387013579608892419337621
e = 8567400787830802078514022663267568911731773624555869237763002695696378792280020113309771609124975352293684207728353672543492823356720699976707093859323464400701867790448407530139117901533363658505645930655786866467985942092946501951999624323378256869592308446534456758895315923365487928014564749516188220862279487168671731379228081536943509358181215979524671634207169067549837218551114394583745914502791477216638887520121667137324171816339493612176033170648271152394902174488081946743170387130116063074812216434961439090056333985936740215049323855762202479578914226998214734884479861260821998427349684935556550063081
d = 1232469622395396469218889751708349467151907650223626994225635164631242097293217718128550558737063386154077755109139775958300907611091492085635673543669085187573255696613456769883789228635610292667064661010664955372858726618902090791188506528035745598139840939591379375169729919736873563055836017738243745303970051534416656553748908366828426784588699254083107027894815872153081302874277587390098999583354945231332573246441509507335660734243065374308829048528297237484972722028464348272874250291318230223625504077095805924369553599544513220190084875161580973720331111370715701450027666156559885101000315322046321541433


class Connection:
    def __init__(self, ip: str, port: int, email: str, password: str):
        self.socket = socket(AF_INET, SOCK_STREAM)
        self.socket.setsockopt(IPPROTO_TCP, TCP_NODELAY, 1)
        self.socket.connect((ip, port))
        self.send_json({"n": f'{n}', "d": f'{d}', "e": f'{e}'})
        self.__user = User(self, self.send_json({"route": "/auth",
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
        self.socket.recv(4)
        data = self.socket.recv(4096).decode('utf-8')
        return json.loads(data)


class User:
    def __init__(self, con: Connection, id: int):
        self.connection = con
        self.id = id

    def get_name(self) -> str:
        data = self.connection.send_json({"route": "/user/get/name", "id": self.id})
        return data["name"]

    def get_status(self) -> str:
        data = self.connection.send_json({"route": "/user/get/status", "id": self.id})
        return data["status"]

    def set_name(self, name: str) -> None:
        self.connection.send_json({"route": "/user/set/name", "id": self.id, "name": name})

    def set_status(self, status: str) -> None:
        self.connection.send_json({"route": "/user/set/status", "id": self.id, "status": status})

    def get_chats(self):
        chats = []

        data = self.connection.send_json({"route": "/user/get/chat_list", "id": self.id})["chats"]
        for chatJson in data:
            chats.append(Chat(self.connection, chatJson["id"]))

        return chats

    def get_configs(self):
        data = self.connection.send_json({"route": "/user/get/configs", "id": self.id})['configs']
        return [Config(self.connection, x["id"]) for x in data]
class Chat:
    def __init__(self, con: Connection, id: int):
        self.connection = con
        self.id = id

    def get_name(self) -> str:
        data = self.connection.send_json({"route": "/chat/get/name", "id": self.id})
        return data["name"]

    def get_invite(self) -> str:
        data = self.connection.send_json({"route": "/chat/get/invite", "id": self.id})
        return data["invite"]

    def get_history(self):
        data = self.connection.send_json({"route": "/chat/get/history", "id": self.id})
        return [Message(self.connection, jsn["id"]) for jsn in data["messages"]]

    def send_message(self, text: str):
        self.connection.send_json({"route": "/chat/send/message", "id": self.id, "message": text})




class Message:
    def __init__(self, con: Connection, id: int):
        self.connection = con
        self.id = id

    def get_text(self):
        return self.connection.send_json({"route": "/chat/message/text", "id": self.id})['text']

    def get_owner(self):
        id: int = self.connection.send_json({"route": "/chat/message/owner", "id": self.id})['id']

        return User(self.connection, id)


class Config:
    def __init__(self, con: Connection, id: int):
        self.connection = con
        self.id = id

    def get_data(self):
        print(self.connection.send_json({"route": "/config/get/data", "id": self.id}))
        return self.connection.send_json({"route": "/config/get/data", "id": self.id})["data"]
