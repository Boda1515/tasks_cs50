#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int number[] = {64, 25, 12, 22, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4, 6, 2, 6, 4, 3,
                     3, 8, 3, 2, 7, 9, 5, 0, 2, 8, 8, 4, 1, 9, 7, 1, 6, 9, 3, 9, 9, 3, 7, 5, 1,
                     0, 5, 8, 2, 0, 9, 7, 4, 9, 4, 4, 5, 9, 2, 3, 0, 7, 8, 1, 6, 4, 0, 6, 7, 9,
                     7, 6, 4, 8, 4, 6, 0, 0, 4, 1, 9, 3, 9, 9, 5, 9, 3, 1, 7, 1, 3, 8, 4, 8, 8,
                     1, 1, 7, 4, 5, 9, 2, 7, 0, 0, 6, 2, 8, 0, 3, 0, 7, 9, 6, 2, 2, 8, 6, 2, 3,
                     4, 7, 1, 8, 1, 0, 5, 6, 9, 5, 8, 4, 1, 9, 7, 1, 6, 9, 3, 9, 9, 3, 7, 5, 1,
                     0, 5, 8, 2, 0, 9, 7, 4, 9, 4, 4, 5, 9, 2, 3, 0, 7, 8, 1, 6, 4, 0, 6, 7, 9,
                     7, 6, 4, 8, 4, 6, 0, 0, 4, 1, 9, 3, 9, 9, 5, 9, 3, 1, 7, 1, 3, 8, 4, 8, 8,
                     1, 1, 7, 4, 5, 9, 2, 7, 0, 0, 6, 2, 8, 0, 3, 0, 7, 9, 6, 2, 2, 8, 6, 2, 3,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0,  9, 5, 5, 8, 3,
                     2, 7, 4, 6, 8, 4, 6, 2, 4, 9, 0, 8, 6, 2, 8, 0, 3, 4, 6, 1, 2, 0, 7, 9, 8};
    int length = sizeof(number) / sizeof(number[0]);
    // printf("length:%i\n", length);
    //        <<    selection_sort    >>
    /*
        For i from 0 to n-1
            IF find smallest number between number[i] and number[n-1]
                Swap the smallest number with number[i]
    */
    for (int i = 0; i < length - 1; i++)
    {
        int max = i;
        for (int x = i + 1; x < length; x++)
        {
            if (number[max] < number[x])
            {
                int temp = number[x];
                number[x] = number[max];
                number[max] = temp;
            }
        }
    }
    //----------print list after sorting-----------//
    for (int i = 0; i < length; i++)
    {
        printf("%i\n", number[i]);
    }
}