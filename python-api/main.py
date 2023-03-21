from avs import *

# 192.168.111.129
# 193.124.33.144
con = Connection("192.168.111.129", 7777, "1@mail.ru", "1235")


user = con.get_logged_user()

print(f"Username: {user.get_name()}")
print(f"Status: {user.get_status()}")
chat = user.get_chats()[0]
while True:
    for msg in chat.get_history():
        print(f"[{msg.get_owner().get_name()}]: {msg.get_text()}")

    chat.send_message(input("Enter message: "))