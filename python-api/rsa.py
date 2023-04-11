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

    def GenerateKeyPair(self):
        p = self.GeneratePrimeNumber()
        q = self.GeneratePrimeNumber()

        n = p*q

        phi = (p - 1) * (q - 1)

        e = 6557

        while gcd(e, phi) != 1:
            e = random.randint(2, phi-1)

        d = mod_inverse(e, phi)

        self.number_n = n
        self.number_e = e
        self.number_d = d

    def Encrypt(self, data: bytes):
        szStep = self.key_size // 8

        encrypted = bytes()
        for i in range(0, len(data), szStep):
            szSizeOfData = szStep if len(data) - i >= szStep else len(data) - i;
            val = int.from_bytes(data[i:i+szSizeOfData], byteorder='big')
            encryptedNumber = pow(val, self.number_e, self.number_n)
            encrypted += bytes([szSizeOfData]) + encryptedNumber.to_bytes((encryptedNumber.bit_length() + 7) // 8, 'big')

        return encrypted



rsa = RSA(1024)
data = rsa.Encrypt("hello world!".encode('utf-8'))

print("done")