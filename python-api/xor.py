from random import randint


def GenerateKey(size: int) -> bytes:
    key = []
    for _ in range(size):
        key.append(randint(1, 255))

    return bytes(key)


def Encrypt(data: list, key: bytes) -> bytes:
    for i in range(len(data)):
        for key_byte in key:
            data[i] ^= key_byte

    return bytes(data)


def Decrypt(data: list, key: bytes) -> bytes:
    for i in range(len(data)):
        for key_byte in reversed(key):
            data[i] ^= key_byte

    return bytes(data)
