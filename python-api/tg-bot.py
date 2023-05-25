from aiogram import *
from avs import *


class RangeNumberInLineButton(types.InlineKeyboardMarkup):
    def __init__(self, numbers):
        super().__init__()
        for number in numbers:
            self.add(types.InlineKeyboardButton(text=str(number), callback_data=str(number)))


class RangeNumberReplyButton(types.ReplyKeyboardMarkup):
    def __init__(self, numbers):
        super().__init__()
        for number in numbers:
            self.add(types.KeyboardButton(text=str(number)))


class ImperiumBot(Bot):
    """
    Основной класс бота
    """

    def __init__(self, token: str):
        super().__init__(token)
        self.__dp = Dispatcher(self)
        self.con = Connection("172.17.0.1", 7777, "1@mail.ru", "1235")

    def run(self):
        @self.__dp.message_handler(commands=['start'])
        async def start_message(message: types.Message):
            await message.answer("Meow")

        @self.__dp.message_handler(commands=['products'])
        async def products(message: types.Message):
            await message.answer("Fetching product list...")

            msg = "*Available Games*\n"
            for product in self.con.get_product_list():
                msg += product.get_name() +"\n"

            await message.answer(msg, parse_mode="Markdown")

        @self.__dp.message_handler(commands=["status"])
        async def status(message: types.Message):
            await message.answer(self.con.get_logged_user().get_status())

        @self.__dp.message_handler(commands=["find"])
        async def status(message: types.Message):
            user_name = message.text.split(" ")[1]
            users = self.con.find_users_by_name(user_name)

            if not len(users):
                await message.answer("Not found :(", parse_mode="Markdown")
                return
            subs = users[0].get_subscriptions();
            info = f"*Name:* {users[0].get_name()}\n*Status:* {users[0].get_status()}\n*Subscriptions:* {len(subs)}\n"

            if len(subs):
                info += "Subscription list: \n"
                for sub in subs:
                    info += f"{'✅' if not sub.is_expired() else '❌'} *Name:* {sub.get_product().get_name()}-*Expires In:* `{sub.get_expiration_date()}`\n"
            await message.answer(info, parse_mode="Markdown")

        executor.start_polling(self.__dp, skip_updates=True)


ImperiumBot('6233239349:dhfhdhdfh').run()
