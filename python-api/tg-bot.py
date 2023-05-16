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
        self.con = Connection("192.168.234.128", 7777, "1@mail.ru", "1235")

    def run(self):
        @self.__dp.message_handler(commands=['start'])
        async def start_message(message: types.Message):
            await message.answer("Meow")

        @self.__dp.message_handler(commands=['products'])
        async def products(message: types.Message):
            await message.answer("Fetching product list...")

            for product in self.con.get_product_list():
                await message.answer(product.get_name())

        @self.__dp.message_handler(commands=["status"])
        async def status(message: types.Message):
            await message.answer(self.con.get_logged_user().get_status())

        executor.start_polling(self.__dp, skip_updates=True)


ImperiumBot('6233239349:AAFzXL4CNCl33QahEMmIQmnBrOUoXw_OCwk').run()
