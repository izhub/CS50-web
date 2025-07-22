#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, string argv[])
{
    string s = argv[1];
    int key = 0;

    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        for (int i = 0, j = strlen(s); i < j; i++)
        {
            if (!isdigit(s[i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
            else
            {
                key = atoi(s);
            }
        }
    }

    string p = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, j = strlen(p); i < j; i++)
    {
        if (isupper(p[i]))
        {
            if ((p[i] + key) >= 'Z')
            {
                p[i] = p[i] - 65;
                p[i] = (p[i] + key) % 26;
                p[i] = p[i] + 65;
                printf("%c", p[i]);
            }
            else
            {
                printf("%c", p[i] + key);
            }
        }
        else if (islower(p[i]))
        {
            if ((p[i] + key) >= 'z')
            {
                p[i] = p[i] - 97;
                p[i] = (p[i] + key) % 26;
                p[i] = p[i] + 97;
                printf("%c", p[i]);
            }
            else
            {
                printf("%c", p[i] + key);
            }
        }
        else
        {
            printf("%c", p[i]);
        }
    }

    printf("\n");
    return 0;
}




/*
1. check single command-line argument, a non-negative integer.
    a. must have only 2 argc
    b. argv[1] will access the key
    c. ensure argument contains only digit characters
    d. convert arg into int, atoi function in stdlib.h
2. prompt for plaintext; get_string
3. Encipher text: iterate over plaintext
    a. if it's alpha, rotate, preserving case
    b. functions isalpha, isupper, islower; A(65)-Z(90), a(97)-z(122)
    c. if neither, print as is
    d. warping alpha
        1. make alpha index, strlen
        2. use Forumla ci = (pi + k) % 26
        3. convert result back to ascii
4. print new line

*/