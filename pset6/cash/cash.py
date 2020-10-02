from cs50 import get_float

change = 0
coins = 0

while True:
    change = int(get_float("Change owned: ") * 100)
    if change > 0:
        break

while change > 0:
    if change >= 25:
        change -= 25
        coins += 1

    elif change >= 10:
        change -= 10
        coins += 1

    elif change >= 5:
        change -= 5
        coins += 1

    elif change >= 1:
        change -= 1
        coins += 1

print(coins)