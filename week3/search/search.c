#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool search_string(void);
int main(void)
{
    int array[] = {25, 29, 4, 47, 65, 8, 9};

    // Search for number by using a (linear search algorithm)
    for (int i = 0; i < 7; i++)
    {
        if (array[i] == 9)
        {
            printf("Found\n");
            return 0;
        }
    }
    printf("Not Found\n");
    return 1;

}

bool search_string(void)
{
    string array[] = {"battleship", "boot", "cannon", "iron", "thimble", "top hat"};

    // Search for number by using a (linear search algorithm)
    // search for string
    for (int i = 0; i < 6; i++)
    {
        if (strcmp(array[i], "boot") == 0)
        {
            printf("Found\n");
            return true;
        }
    }
    printf("Not Found\n");
    return false;
}