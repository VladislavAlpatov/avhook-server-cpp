from avs import *


con = Connection("192.168.111.128", 7777, "1@mail.ru", "1235")
user = con.get_logged_user()

for chat in user.get_chats():
    print(chat.get_name())