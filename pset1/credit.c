#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long creditcard = 0;
    do
    {
        creditcard = get_long("Please enter credit card number: \n");
    }
    while (creditcard == 0);
    int cofd = 0;
    long r = creditcard;
    while (r != 0)
    {
        r = r / 10;
        cofd++;
    }
    long cr = creditcard;
    int temp = 0;
    while (cr != 0)
    {
        temp += cr % 10;
        cr = cr / 10;
        int i = (cr % 10) * 2;
        cr = cr / 10;
        if (i > 9)
        {
            temp += i % 10;
            i = i / 10;
            temp += i % 10;
        }
        else
        {
            temp += i;
        }
    }
    temp = temp % 10;
    long ftd = creditcard;
    while (ftd >= 100)
    {
        ftd = ftd / 10;
    }
    int fd = ftd / 10;
    if (temp == 0 && (ftd == 34 || ftd == 37) && cofd == 15)
    {
        printf("AMEX\n");
    }
    else if (temp == 0 && (ftd == 51 || ftd == 52 || ftd == 53 || ftd == 54 || ftd == 55) && cofd == 16)
    {
        printf("MASTERCARD\n");
    }
    else if (temp == 0 && fd == 4 && (cofd == 13 || cofd == 16))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
