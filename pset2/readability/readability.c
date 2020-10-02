#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");

    int letter = 0;
    int word = 0;
    int count_letters = 0;
    int count_words = 0;
    int count_sentences = 0;

    //counting the number of letters, words and sentences
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        letter = isalpha(text[i]);
        word = isspace(text[i]);

        if (letter != 0)
        {
            count_letters++;
        }
        else if (word != 0)
        {
            count_words++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count_sentences++;
        }
    }
    count_words++;

    //calculating the L
    float L = (((float) count_letters / (float) count_words)) * 100;

    //calculating the S
    float S = (((float) count_sentences / (float) count_words)) * 100;

    //calculating the Coleman-Liau index
    float index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 0 && index <= 16)
    {
        printf("Grade %i\n", (int) index);
    }
    else
    {
        printf("Grade 16+\n");
    }
}