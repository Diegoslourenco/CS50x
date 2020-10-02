from cs50 import get_int

while True:
    height = get_int("Height: ")

    if height > 0 and height <= 8:
        break

for i in range(height):
    for j in range(height):
        if j < height - 1 - i:
            print(" ", end="")
        else:
            print("#", end="")

    print("  ", end="")

    for k in range(i + 1):
        print("#", end="")

    print()