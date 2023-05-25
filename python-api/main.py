from math import ceil

from avs import *
print("start")
# 192.168.111.129
# 193.124.33.144
con = Connection("172.17.0.1", 7777, "1@mail.ru", "1235")

user = con.get_logged_user()

users = con.find_users_by_name("Mercuric")

print(len(users))