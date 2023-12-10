#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string names;
    string nums;
}
pb;
int main(void)
{
    pb array[2];
    array[0].names = "Abdelrahman";
    array[0].nums = "01275322456";

    array[1].names = "David";
    array[1].nums = "+1-949-468-2750";
    // Search for name.
    string n = get_string("Enter the name: ");
    for (int i = 0; i < 2; i++)
    {
        if (strcmp(array[i].names, n) == 0)
        {
            printf("Found %s\n", array[i].nums);
            return 0;
        }
    }
    printf("Not Found\n");
    return 1;
}