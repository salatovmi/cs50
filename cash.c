#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float x;
    do
    {
        x = get_float("How much changed is owned: \n");
    }
    while (x <= 0);
    int coins = round(x * 100);
    int result = 0;
    do
    {
        if(coins >= 25)
        {
            result += 1;
            coins -= 25;
        }
        else if(coins >= 10)
        {
            result += 1;
            coins -= 10;
        }
        else if(coins >= 5)
        {
            result += 1;
            coins -= 5;
        }
        else if(coins >= 1)
        {
            result += 1;
            coins -= 1;
        }
    }
    while (coins > 0);
    printf("%i\n", result);
}
