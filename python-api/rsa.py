import random
import secrets
from sympy import isprime
from math import gcd
from sympy import mod_inverse


class RSA:
    def __init__(self, key_size: int):
        self.key_size = key_size

        self.number_n = None
        self.number_e = None
        self.number_d = None
        self.GenerateKeyPair()

    def GeneratePrimeNumber(self):
        while True:
            random_number = secrets.randbits(self.key_size) | 1 << (self.key_size - 1)
            if isprime(random_number):
                return random_number

    def GetModulusSize(self) -> int:
        return (self.number_n.bit_length() + 7) // 8

    def GetKeySize(self) -> int:
        return int(self.GetModulusSize() / 2)

    def GenerateKeyPair(self):
        p = self.GeneratePrimeNumber()
        q = self.GeneratePrimeNumber()

        n = p * q

        phi = (p - 1) * (q - 1)

        e = 65537

        while gcd(e, phi) != 1:
            e = random.randint(2, phi - 1)

        d = mod_inverse(e, phi)

        self.number_n = n
        self.number_e = e
        self.number_d = d

    def Encrypt(self, data: bytes):
        szStep = self.GetKeySize()

        encrypted = bytes()
        for i in range(0, len(data), szStep):
            szSizeOfData = szStep if len(data) - i >= szStep else len(data) - i
            val = int.from_bytes(data[i:i + szSizeOfData], byteorder='big')
            encryptedNumber = pow(val, self.number_e, self.number_n)
            szEncNumberSize = int((encryptedNumber.bit_length() + 7) // 8)

            encrypted += bytes([szSizeOfData] + [0 for _ in range(szStep*2-szEncNumberSize)]) + encryptedNumber.to_bytes(szEncNumberSize, 'big')

        return encrypted
