// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool has_upper = false;
    bool has_lower = false;
    bool has_num = false;
    bool has_symbol = false;
    for (int l = 0; l < strlen(password); l++)
    {

        if (islower(password[l]))
        {
            has_lower = true;
            for (int u = 0; u < strlen(password); u++)
            {
                if (isupper(password[u]))
                {
                    has_upper = true;
                    for (int d = 0; d < strlen(password); d++)
                    {
                        if (isdigit(password[d]))
                        {
                            has_num = true;
                            for (int s = 0; s < strlen(password); s++)
                            {
                                if (ispunct(password[s]))
                                {
                                    has_symbol = true;
                                    return true;
                                }
                            }
                        }
                    }
                }
            }

        }
    }
/*
// for check whose the error.
    printf("has_lower:%i\n", has_lower);
    printf("has_upper:%i\n", has_upper);
    printf("has_num:%i\n", has_num);
    printf("has_symbol:%i\n", has_symbol);
*/
    return false;
}
