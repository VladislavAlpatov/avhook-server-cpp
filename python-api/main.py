from avs import *


con = Connection("192.168.111.128", 7777, "1@mail.ru", "1235")

print(con.get_logged_user().get_name())