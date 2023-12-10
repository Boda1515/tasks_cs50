#include <cs50.h>
#include <stdio.h>

typedef struct
{
    string name;
    int number;
}person;

int main (void)
{
    // ----Bubble_sort----//
    person persons[3];
    persons[0].name = "Abdelrahman";
    persons[0].number = 3;
    persons[1].name = "Hany";
    persons[1].number = 2;
    persons[2].name = "Marzouk";
    persons[2].number = 1;
    for (int i = 0; i < 3 - 1; i++)
    {
        for (int x = 0; x < 3 - i - 1; x++)
        {
            if (persons[x].number > persons[x + 1].number)
            {
                person temp = persons[x];
                persons[x] = persons[x + 1];
                persons[x + 1] = temp;
            }
        }
    }
    // --------print all--------- //
    for (int i =0 ; i < 3; i++)
    {
        printf("%s: %i\n", persons[i].name ,  persons[i].number);
    }
}