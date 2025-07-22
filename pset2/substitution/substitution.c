#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    string s = argv[1];
    bool match = false;

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        for (int i = 0, l = strlen(s);  i < l; i++)
        {
            for (int j = i + 1; j < l; j++)
            {
                if (s[i] == s[j])
                {
                    match = true; // (strcmp (s[i], s[j]) == 0)
                }
            }

            if (!isalpha(s[i]))
            {
                printf("Key must only contain alphabetic characters.\n");
                return 1;
            }
            else if (l != 26)
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
            else if (match == true)
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    string p = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        if (isupper(p[i]))
        {
            int q = p[i] - 65;
            for (int j = 0, l = strlen(s); j < l; j++)
            {
                if (j == q)
                {
                    printf("%c", toupper(s[j]));
                }
            }
        }
        else if (islower(p[i]))
        {
            int q = p[i] - 97;
            for (int j = 0, l = strlen(s); j < l; j++)
            {
                if (j == q)
                {
                    printf("%c", tolower(s[j]));
                }
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
key validation:
 check key length - Key must contain 26 characters.
 check for non-alphabetical characters - Key must contain 26 characters.
 checkfor repeated characters (case-insensitive) - Key must not contain repeated characters

Encipher
 for each alpha character, determine what letter it maps to
 preserve case
 leave non-alpha characters as-is

A(65)-Z(90), a(97)-z(122)


*/