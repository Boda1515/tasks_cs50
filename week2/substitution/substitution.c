#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
bool contain_26(string k);
bool valid(string key);
char rotate(char c, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        // No command-line argument at all.
        // Providing too many command-line arguments
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (argc == 2)
    {
        if (contain_26(argv[1]) && valid(argv[1]))
        {
            string plaintext = get_string("plaintext:  ");
            printf("ciphertext: ");
            for (int i = 0, len = strlen(plaintext); i < len; i++)
            {
                char encrypted = rotate(plaintext[i], argv[1]);
                printf("%c", encrypted);
            }
            printf("\n");
            return 0;
        }
        else if (!contain_26(argv[1]))
        {
            // If a user doesn’t provide a valid key
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else if (!valid(argv[1]))
        {
            printf("The key must contain only unique upper case letter.\n");
            return 1;
        }
    }
}
//////////////////////////////////////MY_FUNCTIONS/////////////////////////////////////////////////////
bool contain_26(string k)
{
    for (int i = 0, len = strlen(k); i < len; i++)
    {
        if (len == 26)
        {
            return true;
        }
        else if (len > 26)
        {
            return false;
        }
        else
        {
            return false;
        }
    }
    return false;
}
/////////////////////////////////////////////////////////////////////
bool valid(string key)
{

    int check = 0;
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        if (isalpha(key[i]))
        {
            if (isupper(key[i]) || islower(key[i]))
            {
                for (int x = i + 1; x < len; x++)
                {
                    if (key[i] == key[x])
                    {
                        // printf("same\n");
                        check += 1;
                    }
                    else
                    {
                        // printf("Not\n")
                        check += 0;
                    }
                }
            }
        }
        else
        {
            check += 1;
        }
    }
    if (check > 0)
    {
        // printf("The key must contain only unique upper case letter.\n");
        return false;
    }
    else
    {
        // printf("key valied.\n");
        return true;
    }
}
//////////////////////////////////////////////////////////////////////
// NQXPOMAFTRHLZGECYJIUWSKDVB
// 'A' or 'a' would be the first index of the string 'B' or 'b' the second and so for.
char rotate(char c, string key)
{
    int alphaptic_index_z;
    if (isupper(c))
    {
        // Subtract the char from 'A' to get indexing 0 alphaptic (alphaptic_index_z ).
        alphaptic_index_z = c - 'A';
        return toupper(key[alphaptic_index_z]);
    }
    // If the characater is lower change in lower
    else if (islower(c))
    {
        // Subtract the char from 'a' to get indexing 0 alphaptic (alphaptic_index_z ).
        alphaptic_index_z = c - 'a';
        return tolower(key[alphaptic_index_z]);
    }

    // If not alphaptic does not change.
    else if (!isalpha(c))
    {
        return c;
    }
    return c;
}