#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>

float average(int n, int n2);

int main(void)
{
    string s =  get_string("Text: ");

    int letters = 0, words = 1, sentences = 0; 
    float index = 0;

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isalpha(s[i]))  //((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') )
        {
            letters++;
        }
        else if (s[i] == ' ')
        {
            words++;
        }
        else if (s[i] == '!' || s[i] == '.' || s[i] == '?')
        {
            sentences++;
        }
    }

    index = 0.0588 * average(letters, words) - 0.296 * average(sentences, words) - 15.8; 
    index = round(index);
    
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 1 && index < 16)
    {
        printf("Grade %.0f\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }
}



float average(int n, int n2)
{
    float avg = (float) n / n2 * 100;

    return avg;
}



/*
Your program should count the number of letters, words, and sentences in the text.
You may assume that a letter is any lowercase character from a to z or any uppercase character from A to Z,
any sequence of characters separated by spaces should count as a word, and that any occurrence of a period,
exclamation point, or question mark indicates the end of a sentence.

Your program should print as output "Grade X" where X is the grade level computed by the Coleman-Liau formula,
rounded to the nearest integer.

If the resulting index number is 16 or higher (equivalent to or greater than a senior undergraduate reading level),
your program should output "Grade 16+" instead of giving the exact index number. If the index number is less than 1,
your program should output "Before Grade 1".

*/
