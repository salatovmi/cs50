from cs50 import get_int

height = 0
while height > 8 or height < 1:
    height = get_int("Choose number between 1 and 8\n")

for i in range(height):
    print(" " * (height - i - 1) + "#" * (i + 1))