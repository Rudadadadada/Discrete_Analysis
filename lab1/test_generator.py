import random
import string
import os

TEST_COUNT = 3
ALPHABET = '0123456789abcdef'


def get_random_item():
    key_size = 32
    value_size = random.randint(1, 2048)

    key = ""
    for _ in range(key_size):
        key += random.choice(ALPHABET)

    value = ""
    for _ in range(value_size):
        value += random.choice(string.ascii_letters + ALPHABET)

    return '\t'.join([key, value])


def make_test():
    arr = []
    for _ in range(random.randint(1, 8)):
        arr.append(get_random_item())

    return arr


def make_directory():
    try:
        os.mkdir('tests')
    except OSError:
        print('The directory already exists\n')


def make_all_tests():
    make_directory()
    for number in range(TEST_COUNT):
        test = open(f'tests/test{number + 1}', 'w+')
        for item in make_test():
            test.write(item + '\n')
        test.close()


if __name__ == "__main__":
    make_all_tests()
