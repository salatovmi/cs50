from cs50 import get_float

x = 0
while x <= 0:
    x = get_float("How much changed is owned: \n")

x = int(round(x * 100))
coins = 0

while x > 0:
    if x >= 25:
        coins += 1
        x -= 25
    elif x >= 10:
        coins += 1
        x -= 10
    elif x >= 5:
        coins += 1
        x -= 5
    elif x >= 1:
        coins += 1
        x -= 1
print(coins)        