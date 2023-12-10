#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    // Make sure every character in argv[1] is a digit
    if (argc == 2 && only_digits(argv[1]))
    {
        // Convert argv[1] from a `string` to an `int`
        int key = atoi(argv[1]);
        // Prompt user for plaintext
        string plaintext = get_string("plaintext:  ");
        // For each character in the plaintext:Rotate the character if it's a letter.
        printf("ciphertext: ");
        for (int i = 0, len = strlen(plaintext); i < len; i++)
        {
            rotate(plaintext[i], key);
        }
        printf("\n");
        return 0;
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

bool only_digits(string s)
{
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

char rotate(char c, int n)
{
    int aiz;
    // If the characater is upper change in upper
    if (isupper(c))
    {
        // Subtract the char from 'A' to get indexing 0 alphaptic (alphaptic_index_z ).
        int alphaptic_index_z = c - 'A';
        aiz = (alphaptic_index_z + n) % 26;
        printf("%c", 'A' + aiz);
        return 'A' + aiz;
    }
    // If the characater is lower change in lower
    else if (islower(c))
    {
        // Subtract the char from 'a' to get indexing 0 alphaptic (alphaptic_index_z ).
        int alphaptic_index_z = c - 'a';
        aiz = (alphaptic_index_z + n) % 26;
        printf("%c", 'a' + aiz);
        return 'a' + aiz;
    }

    // If not alphaptic does not change.
    else if (!isalpha(c))
    {
        printf("%c", c);
        return c;
    }
    return c;
}