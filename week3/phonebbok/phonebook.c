#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Arrays of strings
    string names[] = {"Carter", "David"};
    string numbers[] = {"+1-617-495-1000", "+1-949-468-2750"};

    // Search for name.
    string name = get_string("Enter the name: ");
    for (int b = 0; b < 2; b++)
    {
        if (strcmp(names[b], name) == 0)
        {
            printf("The name %s has phone number: %s\n", name, numbers[b]);
            return 0;
        }
    }
    printf("The name %s not found\n", name);
    return 1;
}