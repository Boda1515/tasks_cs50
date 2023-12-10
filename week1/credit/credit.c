#include <cs50.h>
#include <math.h>
#include <stdio.h>
int main(void)
{
    long number = get_long("Number: ");
    // temp variable to store the value of digit.
    long d = number;
    // for condition
    long num_digits = floor(log10(number)) + 1;
    // store last digit
    long sum_ld = 0;
    // store second last digit
    long sum_sld = 0;
    // total number of last and second last digit.
    long total;
    // printf("num_digits:%ld\n",num_digits);
    for (long n = 1; n - 1 < num_digits; n++)
    //((number /(long) pow( 10, n-1)) % 10) != d
    {
        d = (number / (long) pow(10, n - 1)) % 10;
        //  printf("d:%ld\n",d);
        //  printf("n:%ld\n",n);
        //   printf("number: %ld\n",number);
        if (n % 2 != 0) // n is odd  == n is  last digit
        {
            // sum of all last digit.
            sum_ld += d;
            // printf("sum_ld:%ld\n",sum_ld);
        }
        if (n % 2 == 0) // n is even  == n is last digit
        {
            // multibly every second last digit by 2.
            d = d * 2;
            // printf("sxnnnn:%ld\n",d);
            //  printf("sxnnnn:%ld\n",d*2);
            if (d == 12)
            {
                // sum of all second last digit.
                sum_sld += 3;
                // printf("2oooooo6:%ld\n",sum_sld);
            }
            else if (d == 10)
            {
                // sum of all second last digit.
                sum_sld += 1;
                //  printf("2oooooo6:%ld\n",sum_sld);
            }
            else if (d == 14)
            {
                // sum of all second last digit.
                sum_sld += 5;
                //  printf("sum_slddddd:%ld\n",sum_sld);
            }
            else if (d == 16)
            {
                // sum of all second last digit.
                sum_sld += 7;
                //  printf("sum_sld:%ld\n",sum_sld);
            }
            else if (d == 18)
            {
                // sum of all second last digit.
                sum_sld += 9;
                //  printf("sum_sld:%ld\n",sum_sld);
            }
            if (d == 0 || d == 2 || d == 4 || d == 6 || d == 8)
            {
                // sum of all second last digit.
                sum_sld += d;
                //  printf("sum_sld:%ld\n",sum_sld);
            }
        }

        // merge to sum together.
        total = sum_ld + sum_sld;
        //  printf("total:%ld\n",total);
        //  printf("*********\n");
    }
    // printf("total:%ld\n",total);
    if (total % 10 == 0)
    {
        if (num_digits == 16)
        {
            if (((number / (long) pow(10, 16 - 1)) % 10) == 5 && ((number / (long) pow(10, 15 - 1)) % 10) == 5)
            {
                printf("MASTERCARD\n");
            }
            else if (((number / (long) pow(10, 16 - 1)) % 10) == 5 && ((number / (long) pow(10, 15 - 1)) % 10) == 4)
            {
                printf("MASTERCARD\n");
            }
            else if (((number / (long) pow(10, 16 - 1)) % 10) == 5 && ((number / (long) pow(10, 15 - 1)) % 10) == 3)
            {
                printf("MASTERCARD\n");
            }
            else if (((number / (long) pow(10, 16 - 1)) % 10) == 5 && ((number / (long) pow(10, 15 - 1)) % 10) == 2)
            {
                printf("MASTERCARD\n");
            }
            else if (((number / (long) pow(10, 16 - 1)) % 10) == 5 && ((number / (long) pow(10, 15 - 1)) % 10) == 1)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        else if (num_digits == 15)
        {
            if (((number / (long) pow(10, 15 - 1)) % 10) == 3 && ((number / (long) pow(10, 14 - 1)) % 10) == 7)
            {
                printf("AMEX\n");
            }
            else if (((number / (long) pow(10, 15 - 1)) % 10) == 3 && ((number / (long) pow(10, 14 - 1)) % 10) == 4)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        if (((num_digits == 16) && ((number / (long) pow(10, 16 - 1)) % 10) == 4))
        {
            printf("VISA\n");
        }
        else if (((num_digits == 13) && ((number / (long) pow(10, 13 - 1)) % 10) == 4))
        {
            printf("VISA\n");
        }
        else if (num_digits != 16 && num_digits != 13 && num_digits != 15)
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
// Traning on the implimntation
/*
********************************************************************
    for (int i = d ; i < x ; i ++ )
        {
            z = i * 2;
            printf("second last digit: %i\n", z);
        }
********************************************************************
    long x = number; // Create a temporary variable to store the number

    while (x > 0) // repeate until the number end
    {
        printf("The x before: %ld\n", x);
        int digit = x % 10; // last digit
        printf("The last digit: %i\n", digit);
        x /= 10; // Delete the last digit
        printf("The x after: %ld\n", x);
    }
*********************************************************************
    else if ((n == 16 && d == 5) || (n == 15 && d == 4))
    {
        printf("MASTERCARD\n");
    }
    else if ((n == 16 && d == 5) || (n == 15 && d == 3))
    {
        printf("MASTERCARD\n");
    }
    else if ((n == 16 && d == 5) || (n == 15 && d == 2))
    {
        printf("MASTERCARD\n");
    }
    else if ((n == 16 && d == 5) || (n == 15 && d == 1))
    {
        printf("MASTERCARD\n");
    }
***********************************************************************
    long s;
    for (long i = 0 ;i < number; i++)
      {
        s = number/=10;
        i = number;
        printf("i:%ld\n",i);
      }
        printf("s:%ld\n",s);
***********************************************************************
   if (total % 10 == 0)
        {
            if ( num_digits == 16)
            {
                if (((number /(long) pow( 10, 16-1)) % 10)==5 || ((number /(long) pow( 10, 15-1)) % 10)== 5)
                {
                    printf("MASTERCARD\n");
                }
                else if (((number /(long) pow( 10, 16-1)) % 10)==5 || ((number /(long) pow( 10, 15-1)) % 10)== 4)
                {
                    printf("MASTERCARD\n");
                }
                else if (((number /(long) pow( 10, 16-1)) % 10)==5 || ((number /(long) pow( 10, 15-1)) % 10)== 3)
                {
                    printf("MASTERCARD\n");
                }
                else if (((number /(long) pow( 10, 16-1)) % 10)==5 || ((number /(long) pow( 10, 15-1)) % 10)== 2)
                {
                    printf("MASTERCARD\n");
                }
                else if (((number /(long) pow( 10, 16-1)) % 10)==5 || ((number /(long) pow( 10, 15-1)) % 10)== 1)
                {
                    printf("MASTERCARD\n");
                }
            }

            else if ( num_digits == 15 )
            {
                if ((n == 15 && d == 3) || (n == 14 && d == 7))
                {
                    printf("AMEX\n");
                }
                else if ((n == 15 && d == 3) || (n == 14 && d == 4))
                {
                    printf("AMEX\n");
                }
            }

             else if ( ((num_digits == 16 ) && ((number /(long) pow( 10, 16-1)) % 10) == 4 )|| ((num_digits == 13 ) && ((number
/(long) pow( 10, 16-1)) % 10) == 4 ))
            {
                printf("VISA\n");
            }

        }

        else
        {
            printf("INVALID\n");
        }
***********************************************************************
*/
