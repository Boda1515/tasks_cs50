#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // Start by getting the index of the last char in the string (the char before the \0).
    // "Abdelrahman"
    int len = strlen(input);
    if (len == 1)
    {
        return atoi(input);
    }
    // Start by getting the index of the last char in the string (the char before the \0).
    int last_index = len - 1;
    // printf("%i\n", len - 1);
    // Convert this char into its numeric value. Can you subtract some char to do this?
    int converted_char = input[len - 1] - '0';
    // printf("%i\n", input[len - 1] - '0');
    // Remove the last char from the string by moving the null terminator one position to the left.
    len -= 1;
    input[len] = '\0';
    // Return this value plus 10 times the integer value of the new shortened string.
    return converted_char + 10 * convert(input);
}