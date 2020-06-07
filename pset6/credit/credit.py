from cs50 import get_int

creditcard = 0
while creditcard <= 0:
    creditcard = get_int("Please enter credit card number: \n")
cofd = 0
r = creditcard
while r != 0:
    r = int(r / 10)
    cofd += 1

cr = creditcard
temp = 0
while cr != 0:
    temp += cr % 10
    cr = int(cr / 10)
    i = (cr % 10) * 2
    cr = int(cr / 10)
    if i > 9:
        temp += i % 10
        i = int(i / 10)
        temp += i % 10
    else:
        temp += i
temp = temp % 10
ftd = creditcard
while ftd >= 100:
    ftd = int(ftd / 10)
fd = int(ftd / 10)
if temp == 0 and (ftd == 34 or ftd == 37) and cofd == 15:
    print("AMEX")
elif temp == 0 and ftd in [51,52,53,54,55] and cofd == 16:
    print("MASTERCARD")
elif temp == 0 and fd == 4 and (cofd == 13 or cofd == 16):
    print("VISA")
else:
    print("INVALID")