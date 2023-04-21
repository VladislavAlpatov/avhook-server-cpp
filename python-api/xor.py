from random import randint


def GenerateKey(size: int) -> bytes:
    key = []
    for _ in range(size):
        key.append(randint(0, 255))

    return bytes(key)


def Encrypt(data: bytes, key: bytes) -> bytes:
    for byte in data:
        for key_byte in key:
            byte ^= key_byte

    return data


def Decrypt(data: bytes, key: bytes) -> bytes:
    for byte in data:
        for key_byte in reversed(key):
            byte ^= key_byte

    return data
