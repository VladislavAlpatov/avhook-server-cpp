from avs import *
# 192.168.111.129
# 193.124.33.144
con = Connection("192.168.111.129", 7777, "1@mail.ru", "1235")


user = con.get_logged_user()

print(f"Username: {user.get_name()}")
print(f"Status: {user.get_status()}")

