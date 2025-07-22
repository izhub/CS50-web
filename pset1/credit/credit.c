#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long n =  get_long("Enter Number: ");
    long n2 = n ;
    int rem, count = 0, checksum = 0;

    while (n != 0)
    {
        rem = n % 10;
        n /= 10;
        count++;
    }

    n = n2;
    n /= 10;
    while (n != 0)
    {
        int r, r2, s;
        s = (n % 10) * 2;
        if (s > 9)
        {
            r = s % 10;
            s = s / 10;
            r2 = s % 10;
            checksum += r + r2;
        }
        else
        {
            checksum += s;
        }
        n /= 100;
    }

    n = n2;
    while (n != 0)
    {
        checksum += n % 10;
        n /= 100;
    }

   int m, m1, c;
    c = checksum % 10;
    m = n2 / pow(10, count - 1); 
    m1 = n2 / pow(10, count - 2); 
     
    if (c == 0 && (count == 13 || count == 16) && m == 4)
    {
        printf("VISA\n"); 
    }
    else if (c == 0 && count == 15 && (m1 == 34 || m1 == 37)) 
    {
        printf("AMEX\n"); 
    }
    else if (c == 0 && count == 16 && (m1 > 50 && m1 < 56))
    {
     printf("MASTERCARD\n"); 
    }
    else if (c != 0 || count != 15 || count != 16 || count != 13)
    {
        printf("INVALID\n");
    }

}

// American Express: 15 digits, starts with 34 or 37
// MasterCard: 16 digits, starts with 51, 52, 53, 54, or 55
// Visa : 13 or 16 digits, starts with 4

// Checksum:
// • Multiply every other digit by 2, starting with second to last digit
// • Add those products' digits together
// • Add the sum of the sum of the digits that weren't multiplied by 2
// • If the total's last digit is 0, number is valid!
// TODO:
// Prompt for input
// Calculate checksum - for last digit
// Check for card length and starting digits
// Print AMEX, MASTERCARD, VISA or INVALID
