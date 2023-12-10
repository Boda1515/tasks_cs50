#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
string clean(string word);

int main(int argc, string argv[])
{
    //---- First we need to accepet one word ----//
    if (argc == 2)
    {
        printf("This the word Befor: %s  After: %s\n", argv[1], clean(argv[1]));
        return 0;
    }
    else
    {
        printf("Enter one word only.\n");
        return 1;
    }
}

char* clean(char* word)
{
    int len = strlen(word);
    if (len == 1)
    {
        printf("%s\n", word);
        return word;
    }
    char* substr = &word[1];
    if (word[0] == word[1])
    {
        printf("%c\n", word[0]);
        return clean(substr);
    }
    char* result = (char*)malloc(len); // allocate memory for result string
    *result = word[0]; // set the first character of the result string
    char* cleaned_substr = clean(substr); // recursively clean the substring
    strcat(result, cleaned_substr); // append the cleaned substring to the result string
    return result;
}