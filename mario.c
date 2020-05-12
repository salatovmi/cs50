#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    string prompt = "Please enter height from 1 to 8.\n";
    do
    {
        height = get_int("%s", prompt);
    }
    while (height < 1 || height > 8);
    for (int a = 0; a < height; a++)
    {
        for (int i = 0; i < height - a - 1; i++)
        {
            printf(" ");
        }
        for (int i = 0; i < a + 1; i++)
        {
            printf("#");
        }
        printf("  ");
        for (int i = 0; i < a + 1; i++)
        {
            printf("#");
        }
        printf("\n");
    }
}
