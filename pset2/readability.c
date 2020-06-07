#import <cs50.h>
#import <stdio.h>
#import <string.h>
#import <math.h>

int countletters(string s);
int countwords(string s);
int countsentences(string s);

int main(void)
{
    string s = get_string("Text: \n");
    int countofletters = countletters(s);
    int countofwords = countwords(s);
    int countofsentences = countsentences(s);
    float indexL = ((float)countofletters / (float)countofwords) * 100;
    float indexS = ((float)countofsentences / (float)countofwords) * 100;
    int index = round(0.0588 * indexL - 0.296 * indexS - 15.8);
    printf("let = %i\n", countofletters);
    printf("words = %i\n", countofwords);
    printf("sent = %i\n", countofsentences);
    printf("L = %.5f\n", indexL);
    printf("S = %.5f\n", indexS);
    printf("index = %i\n", index);

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    } 
    else
    {
        printf("Grade %i\n", index);
    }
}

int countletters(string s)
{   
    int countofletters = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {   
        int ch = s[i];
        if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122))
        {
            countofletters++;
        }
    }
    return countofletters;
}

int countwords(string s)
{
    int countofwords = 1;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        int ch = s[i];
        if (ch == 32)
        {
            countofwords++;
        }
    }
    return countofwords;
}

int countsentences(string s)
{
    int countofsentences = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        int ch = s[i];
        if (ch == 33 || ch == 46 || ch == 63)
        {
            countofsentences++;
        }
    }
    return countofsentences;
}


