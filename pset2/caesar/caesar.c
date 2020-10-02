#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //counting command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //acessing and validating the key
    int number = 0;

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        number = isdigit(argv[1][i]);

        if (number == 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    //defining key
    int k = atoi(argv[1]);

    //applying the Caesar's cipher
    string plain_text = get_string("plaintext: ");
    string cipher_text = plain_text;
    int p = 0;
    int c = 0;

    for (int i = 0, n = strlen(plain_text); i < n; i++)
    {
        if (isalpha(plain_text[i]) != 0)
        {
            if (isupper(plain_text[i]) != 0)
            {
                p = (int) plain_text[i] - 65;
                c = (p + k) % 26;
                cipher_text[i] = c + 65;
            }
            else
            {
                p = (int) plain_text[i] - 97;
                c = (p + k) % 26;
                cipher_text[i] =  c + 97;
            }
        }
        else
        {
            cipher_text[i] = plain_text[i];
        }
    }

    printf("ciphertext: %s\n", cipher_text);
    return 0;
}