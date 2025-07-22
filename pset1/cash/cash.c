#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float input;
    int change;
    int tc = 0; //total coins
    do
    {
        input = get_float("Change owed: ");
    }
    while (input < 0);
    change = round(input * 100);
    
    while (change > 0)
    {
        if (change >= 25)
        {
            change -= 25;
            tc++;
        }
        else if (change >= 10)
        {
            change -= 10;
            tc++;
        }
        else if (change >= 5)
        {
            change -= 5;
            tc++;
        }
        else
        {
            change--;
            tc++;
        }
    }
    printf("Total coins: %i\n", tc);
}