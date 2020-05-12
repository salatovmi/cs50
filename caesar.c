#import <cs50.h>
#import <stdio.h>
#import <string.h>
#import <ctype.h>
#import <stdlib.h>

string encrypt(int key, string s);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("%s key\n", argv[0]);
        return 1;
    }
    else
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (!(isdigit(argv[1][i])))
            {
                printf("%s key\n", argv[0]);
                return 1;
            }
        }
        printf("Success\n");
    }
    int key = atoi(argv[1]) % 26;
    string plaintext = get_string("plaintext: ");
    string ciphertext;
    if (key != 0)
    {
        ciphertext = encrypt(key, plaintext);
    }
    else
    {
        ciphertext = plaintext;
    }
    printf("ciphertext: %s\n", ciphertext);
}

string encrypt(int key, string s)
{   
    string result = s;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isupper(s[i]))
        {   
            int ch = s[i] + key;
            if (ch > 90)
            {
                result[i] = (char)(ch - 26);
            }
            else
            {
                result[i] = (char)ch;
            }
        }
        else if (islower(s[i]))
        {
            int ch = s[i] + key;
            if (ch > 122)
            {
                result[i] = (char)(ch - 26);
            }
            else
            {
                result[i] = (char)ch;
            }
        }
        else
        {
            result[i] = s[i];
        }
        printf("%s\n", result);
    }
    return result;
}
