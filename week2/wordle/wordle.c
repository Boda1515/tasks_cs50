#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET "\e[0;39m"

// user-defined function prototypes
string get_guess(int wordsize);
int check_word(string guess, int wordsize, int status[], string choice);
void print_word(string guess, int wordsize, int status[]);
// my_func
bool only_digit(string argv);

int main(int argc, string argv[])
{
    // ensure proper usage
    // TODO #1
    int wordsize = 0;
    if (argc == 2)
    {
        // ensure argv[1] is either 5, 6, 7, or 8 and store that value in wordsize instead
        // TODO #2
        if (only_digit(argv[1]))
        {
            int key = atoi(argv[1]);
            wordsize += key;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        printf("Usage: ./wordle wordsize\n");
        return 1;
    }

    // open correct file, each file has exactly LISTSIZE words
    char wl_filename[6];
    sprintf(wl_filename, "%i.txt", wordsize);
    FILE *wordlist = fopen(wl_filename, "r");
    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        return 1;
    }

    // load word file into an array of size LISTSIZE
    char options[LISTSIZE][wordsize + 1];

    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]);
    }

    // pseudorandomly select a word for this game
    srand(time(NULL));
    string choice = options[rand() % LISTSIZE];

    // allow one more guess than the length of the word
    int guesses = wordsize + 1;
    bool won = false;

    // print greeting, using ANSI color codes to demonstrate
    printf(GREEN "This is WORDLE50" RESET "\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);

    // main game loop, one iteration for each guess
    for (int i = 0; i < guesses; i++)
    {
        // obtain user's guess
        string guess = get_guess(wordsize);
        // array to hold guess status, initially set to zero
        int status[wordsize];
        // set all elements of status array initially to 0, aka WRONG
        // TODO #4
        for (int c = 0; c < wordsize; c++)
        {
            status[c] = WRONG;
        }
        // Calculate score for the guess
        int score = check_word(guess, wordsize, status, choice);
        printf("Guess %i: ", i + 1);
        // Check code.
        // printf("Score : %i", score);
        // printf("choice %s: ", choice);
        // Print the guess
        print_word(guess, wordsize, status);

        // if they guessed it exactly right, set terminate loop
        if (score == EXACT * wordsize)
        {
            won = true;
            printf("You won!\n");
            printf("The target word was: " GREEN "%s" RESET "\n", choice);
            break;
        }
    }

    // Print the game's result
    // TODO #7
    if (won == false)
    {
        string guess = get_guess(wordsize);
        int status[wordsize];
        int score = check_word(guess, wordsize, status, choice);
        printf("You lose!\n");
        printf("Score: %i\n", score);
        printf("The target word was: " GREEN "%s" RESET "\n", choice);
    }
    // that's all folks!
    return 0;
}

string get_guess(int wordsize)
{
    string guess = "";
    // ensure users actually provide a guess that is the correct length
    // TODO #3
    // Word does not contain any num or punc.
    int len;
    do
    {
        guess = get_string("Input a %i-letter word: ", wordsize);
        len = strlen(guess);
        for (int i = 0; i < len; i++)
        {
            // Take char and convert it to lower case (optional).
            guess[i] = (char) tolower((unsigned char) guess[i]);
        }
    }
    while (len < wordsize || len > wordsize);
    return guess;
}
int check_word(string guess, int wordsize, int status[], string choice)
{
    // compare guess to choice and score points as appropriate, storing points in status
    // TODO #5
    // HINTS
    // iterate over each letter of the guess
    // iterate over each letter of the choice
    // compare the current guess letter to the current choice letter
    // if they're the same position in the word, score EXACT points (green) and break so you don't compare that letter further
    // if it's in the word, but not the right spot, score CLOSE point (yellow)
    // keep track of the total score by adding each individual letter's score from above
    int score = 0;
    for (int x = 0; x < wordsize; x++)
    {
        if (guess[x] == choice[x])
        {
            status[x] = EXACT;
            score += 2;
        }
        else if (guess[x] != choice[x])
        {
            for (int q = 0; q < wordsize; q++)
            {
                if (choice[q] == guess[x])
                {
                    status[x] = CLOSE;
                    score += 1;
                    break;
                }
                else
                {
                    status[x] = WRONG;
                    score += 0;
                }
            }
        }
    }
    return score;
}

void print_word(string guess, int wordsize, int status[])
{
    // print word character-for-character with correct color coding, then reset terminal font to normal
    // TODO #6
    for (int i = 0; i < wordsize; i++)
    {
        if (status[i] == EXACT)
        {
            printf(GREEN "%c" RESET, guess[i]);
        }
        else if (status[i] == CLOSE)
        {
            printf(YELLOW "%c" RESET, guess[i]);
        }
        else
        {
            printf(RED "%c" RESET, guess[i]);
        }
    }
    printf("\n");
}

bool only_digit(string argv)
{
    int key = atoi(argv);
    for (int i = 0, len = strlen(argv); i < len; i++)
    {
        int is = isdigit(argv[i]);
        if (is)
        {
            if (key == 5 || key == 6 || key == 7 || key == 8)
            {

                return true;
            }
            else
            {
                printf("Error: wordsize must be either 5, 6, 7, or 8\n");
                return false;
            }
        }
        else if (isalpha(argv[i]))
        {
            printf("It is char not num\n");
            return false;
        }
    }
    return false;
}