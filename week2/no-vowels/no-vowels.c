// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>
string replace(string word);

int main(int argc, string argv[])
{
    // argc count the input in cmd including ./file = 1.
    // here we need one input no less or more.
    if (argc == 2)
    {
        // argv[1] mean the word that i pass it.
        // we stor it in variable word.
        string word = argv[1];
        // Perform the desired conversion on the 'word' variable
        replace(word);
        return 0;
    }
    else
    {
        printf("Wrong input!");
        // return 1 mean that program has error.
        return 1;
    }
}

string replace(string word)
{
    int length = strlen(word);
    char vowels[10] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
    for (int i = 0; i < length; i++)
    {
        // flag to indicate if the character is a vowel.
        int is_vowel = 0;
        // loop to check if the char is vowel.
        for (int x = 0; x < 10; x++)
        {
            if (word[i] == vowels[x])
            {
                // set the flag to indicate the character is found.
                is_vowel = 1;
                switch (word[i])
                {
                    // When you wanna to write or in switch we use two case.
                    case 'a':
                    case 'A':
                        word[i] = 6;
                        printf("6");
                        break;

                    case 'e':
                    case 'E':
                        word[i] = '3';
                        printf("3");
                        break;

                    case 'i':
                    case 'I':
                        word[i] = '1';
                        printf("1");
                        break;

                    case 'o':
                    case 'O':
                        word[i] = '0';
                        printf("0");
                        break;

                    default:
                        printf("u");
                        break;
                }
                // break the loop2 once a vowel is found.
                break;
            }
        }
        if (!is_vowel)
        {
            printf("%c", word[i]);
        }
    }
    printf("\n");
    return word;
}