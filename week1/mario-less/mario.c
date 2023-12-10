#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height:");
    }
    while (height < 1 || height > 8);

    for (int i = 0; i < height; i++)
    {
        for (int m = height; m - 1 > i; m--)
        {
            // number of columns.
            printf(" ");
        }

        for (int x = 0; x < i; x++)
        {
            // number of columns.
            printf("#");
        }
        // number of rows.
        printf("#\n");
    }
}

/*
for (int i = 0; i < n; i++)
{
    for (int j = 0; j < n; j++)
    {
          printf("#");
    }
      printf("\n");
}
*/