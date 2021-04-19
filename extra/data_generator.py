import random


def generate_data(quantity, file):
    file.write(str(quantity) + "\n")
    for element in range(0, quantity):
        file.write(str(random.randint(-1000, 1000)) + "\n")


if __name__ == '__main__':
    myFile = open("data.txt", "w")
    generate_data(1000, myFile)
