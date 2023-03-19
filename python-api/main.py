from avs import *


con = Connection("192.168.111.128", 7777, "1@mail.ru", "1235")
user = con.get_logged_user()
user.set_status("We live in twilight world, and there no friends at dusk")
print(con.get_logged_user().get_status())