from math import ceil

from avs import *
print("start")
# 192.168.111.129
# 193.124.33.144
con = Connection("192.168.234.128", 7777, "1@mail.ru", "1235")

user = con.get_logged_user()

for sub in user.get_subscriptions():
    print(sub.get_expiration_date())
