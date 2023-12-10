#include <cs50.h>
#include <stdio.h>
#include <string.h>

int factorial(int n);
int main(void)
{
    int n = get_int("Enter the number: ");
    printf("factorial of %i is : %i\n", n, factorial(n));
}

int factorial(int n)
{
    // End of recursion.
    if (n == 1)
    {
        return 1;
    }
    return n * factorial(n - 1);
}