#import <cs50.h>
#import <stdio.h>
#import <string.h>
#import <ctype.h>
#import <stdlib.h>

char key[26];
int checkForUniqueAndLetters(string s);
string encrypt(string plaintext);

int main(int argc, string argv[])
{   
    if (argc != 2 || strlen(argv[1]) != 26)
    {
        printf("Print only 26 letters\n");
        return 1;
    }
    if (checkForUniqueAndLetters(argv[1]) == 1)
    {
        return 1;
    }
    string plaintext = get_string("plaintext: ");
    string res = encrypt(plaintext);
    printf("ciphertext: %s\n", res);
}

int checkForUniqueAndLetters(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {   
        if ((s[i] >= 97 && s[i] <= 122) || (s[i] >= 65 && s[i] <= 90))
        {
            key[i] = tolower(s[i]);
            int count = 0;
            for (int a = 0, m = strlen(s); a < m; a++)
            {   
                if (key[i] == tolower(s[a]))
                {
                    count++;
                }
                if (count > 1)
                {
                    printf("Duplicate of %c\n", key[i]);
                    return 1;
                }
            }
        }
        else
        {
            printf("Key should contain only letters\n");
            return 1;
        }
    }
    return 0;
}

string encrypt(string plaintext)
{
    string result = plaintext;
    for (int i = 0, m = strlen(plaintext); i < m; i++)
    {
        if (plaintext[i] > 64 && plaintext[i] < 91)
        {
            result[i] = toupper(key[plaintext[i] - 65]);
        }
        else if (plaintext[i] > 96 && plaintext[i] < 123)
        {
            result[i] = key[plaintext[i] - 97];
        }
    }
    return result;
}
