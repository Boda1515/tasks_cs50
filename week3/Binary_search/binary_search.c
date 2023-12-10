#include <cs50.h>
#include <stdio.h>

int recursive_binary(int number[], int num, int left, int right);
int main(void)
{
    int number[] = {5, 9, 7, 6, 2, 3};
    int length = sizeof(number) / sizeof(number[0]);
    // sorting the number array in Assinding order.
       // The sorting using Bubble Sort.
   // psedocode --
    /*
        Repeat n-1 times
            For i from 0 to n-2
                IF num[i] and num[i+1] out of order
                    Swap them
            IF no swap
                Quit
   */
    for (int i = 0; i < length - 1; i++)
    {
        int temp;
        for (int x = 0; x < length - i - 1; x++)
        {
            if (number[x] > number[x + 1])
            {
                temp = number[x];
                number[x] = number[x + 1];
                number[x + 1] = temp;
            }
        }
    }
        /////////////////--print to ditected that the sorting is run well--///////////////////////
    for (int i = 0; i < length; i++)
    {
        printf("%i ", number[i]);
    }
    printf("\n");
    //---------------------------------------------------------------------------------------------------//
       // The sorting using Bubble Sort.
   // psedocode -- 
    /*  
        Repeat n-1 times
            For i from 0 to n-2
                IF num[i] and num[i+1] out of order
                    Swap them
            IF no swap 
                Quit
   */
    for (int i = 0; i < length - 1; i++)
    {   
        int temp;
        for (int x = 0; x < length - 2; x++)
        {
            if (number[x] > number[x + 1])
            {
                temp = number[x];
                number[x] = number[x + 1];
                number[x + 1] = temp;   
            }
        }
    }
    /////////////////--print to ditected that the sorting is run well--///////////////////////
    for (int i = 0; i < length; i++)
    {
        printf("%i ", number[i]);
    }
    printf("\n");
    /////////////////--FInd number that user prompt--/////////////////////////
    int num = get_int("num: ");
    int result = recursive_binary(number, num, 0, length - 1);
    if (result == -1)
    {
        printf("NOT FOUND\n");
    }
    else
    {
        printf("The index of your num %i is: %i\n", num, result);
    }
}

int recursive_binary(int number[], int num, int left, int right)
{
    if (right < left)
    {
        return -1;
    }
    int middle = left + (right - left) / 2;
    if (num == number[middle])
    {
        // Notice that return here is index not the number.
        return middle;
    }
    else if (num < number[middle])
    {
        return recursive_binary(number, num, left, middle - 1);
    }
    else
    {
        return recursive_binary(number, num, middle + 1, right);
    }
}