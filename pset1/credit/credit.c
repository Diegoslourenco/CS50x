#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //receiving the credit card number
    long n;
    do
    {
        n = get_long("Number: ");
    }
    while (n < 0);

    //calculating the checksum
    int sum = 0;
    long m = n;
    long c = n;
    int p = n / 1000000000000;
    string card = "";

    while (m > 0)
    {
        sum += m % 10;
        //printf("Sum: %i\n", sum);
        m /= 10;
        if ((m % 10 * 2) > 9)
        {
            sum += (m % 10 * 2) % 10 + (m % 10 * 2) / 10;
        }
        else
        {
            sum += m % 10 * 2;
        }
        m /= 10;
    }
    sum = sum % 10;

    //verifing the length
    int cont = 0;

    while (c > 0)
    {
        c /= 10;
        cont++;
    }

    //Checking the type of the card
    if (sum == 0)
    {
        if ((cont == 15) && ((p / 10) == 34 || (p / 10) == 37))
        {
            card = "AMEX";
        }
        else if ((cont == 16) && ((p / 100) == 51 || (p / 100) == 52 || (p / 100) == 53 || (p / 100) == 54 || (p / 100) == 55))
        {
            card = "MASTERCARD";
        }
        else if ((cont == 13 || cont == 16) && (p == 4 || (p / 1000) == 4))
        {
            card = "VISA";
        }
        else
        {
            card = "INVALID";
        }
    }
    else
    {
        card = "INVALID";
    }
    printf("%s\n", card);
}