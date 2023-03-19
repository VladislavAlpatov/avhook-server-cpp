from avs import *


con = Connection("192.168.111.128", 7777, "1@mail.ru", "1235")


user = con.get_logged_user()
print(f"Username: {user.get_name()}")
print(f"Status: {user.get_status()}")


for chat in user.get_chats():
    print(f"History of '{chat.get_name()}':")

    for message in chat.get_history():
        print(message.get_text())