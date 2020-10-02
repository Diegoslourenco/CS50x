#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    //command-line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }

    //validating if the key has only alphabetical letters
    int n = strlen(argv[1]);

    for (int i = 0; i < n; i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            printf("key must contain only letters\n");
            return 1;
        }
    }

    //validating if the key has not containing each letter once
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n ; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("key must not repeat characters\n");
                return 1;
            }
        }
    }

    //putting the key in k
    string k = argv[1];

    //receiving the plaintext
    string plaintext = get_string("plaintext: ");

    //applying the key to the plaintext received
    string ciphertext = plaintext;
    int p = 0;

    for (int i = 0, m = strlen(plaintext); i < m; i++)
    {
        if (isalpha(plaintext[i]) != 0)
        {
            if (isupper(plaintext[i]) != 0)
            {
                p = (int) plaintext[i] - 65;
                if (isupper(k[p]) != 0)
                {
                    ciphertext[i] = k[p];
                }
                else
                {
                    ciphertext[i] = toupper(k[p]);
                }
            }
            else
            {
                p = (int) plaintext[i] - 97;
                if (isupper(k[p]) != 0)
                {
                    ciphertext[i] = tolower(k[p]);
                }
                else
                {
                    ciphertext[i] = (k[p]);
                }
            }
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    //outputing the ciphertext
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}