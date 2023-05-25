from math import ceil

from avs import *
print("start")
# 192.168.111.129
# 193.124.33.144
con = Connection("172.17.0.1", 7777, "1@mail.ru", "1235")

user = con.get_logged_user()

print(user.get_name())
print(user.get_status())

for sub in user.get_subscriptions():
    print(f'{sub.get_expiration_date()}')
