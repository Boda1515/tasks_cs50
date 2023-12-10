#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int len = get_int("Lingth: ");

    //func to print the prymid.
    for (int i = 0; i < len; i++)
    {
        for (int x = 0; x < i + 1; x++)
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}
