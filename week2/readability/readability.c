#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    /*
    printf("%i letters\n", count_letters(text));
    printf("%i words\n", count_words(text));
    printf("%i sentences\n", count_sentences(text));
    */
    // L is the average number of letters per 100 words in the text
    float L = (count_letters(text) / (float) count_words(text)) * 100;
    // S is the average number of letters per 100 words in the text
    float S = (count_sentences(text) / (float) count_words(text)) * 100;
    // Coleman-Liau formula
    float index = 0.0588 * L - 0.296 * S - 15.8;
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}
// This func to count how many number of letters in the text.
int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isupper(text[i]))
        {
            letters += 1;
        }
        else if (islower(text[i]))
        {
            letters += 1;
        }
        else
        {
            letters += 0;
        }
    }
    // num_letters is number of letters in the text.
    return letters;
}

// func count numbers of words by space
int count_words(string text)
{
    // I put the 1 as intial value to word to count the last space in text.
    int word = 1;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // isblank is a great func to know a tab or a space in string.
        if (isblank(text[i]))
        {
            word += 1;
        }
    }
    return word;
}

// func to count sentences in the text.
int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences += 1;
        }
    }
    return sentences;
}