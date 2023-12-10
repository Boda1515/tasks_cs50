#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    string Message = get_string("Message: ");
    int binary[BITS_IN_BYTE];
    for (int i = 0, len = strlen(Message); i < len; i++)
    {
        // variable (convert) to store the converted char to his Dec number.
        int convert = Message[i];
        for (int x = 0; x < BITS_IN_BYTE; x++)
        {
            binary[x] = convert % 2;
            convert /= 2;
        }
        // This loop to store the values (1.0) from right to left.
        for (int x = BITS_IN_BYTE - 1; x >= 0; x--)
        {
            print_bulb(binary[x]);
        }
        // After every char print new line.
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}