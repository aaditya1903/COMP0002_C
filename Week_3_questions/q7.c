#include <stdio.h>

int prime(int a)
{
    int number;

    if (a < 2)
    {
        return 0;
    }

    for (number = 2; number <= a / 2; number++)
    {
        if (a % number == 0)
        {
            return 0;
        }
    }
    return 1;
}

void twinPrimes(int lowlim, int uplim)
{
    printf("Twin prime numbers between %d and %d are:\n", lowlim, uplim);

    for (int i = lowlim; i <= uplim; i++)
    {
        if (prime(i) && (prime(i + 2)))
        {
            printf("(%d, %d)\n", i, i + 2);
        }
        if (prime(i) && (prime(i + 1)))
        {
            printf("(%d, %d)\n", i, i + 1);
        }
    }
}

int main() {
    int lowerLimit, upperLimit;

    printf("Enter the lower limit: ");
    scanf("%d", &lowerLimit);
    printf("Enter the upper limit: ");
    scanf("%d", &upperLimit);

    if (lowerLimit >= 0 && lowerLimit <= upperLimit)
    {
        twinPrimes(lowerLimit, upperLimit);
    } 
    else
    {
        printf("Invalid range.\n");
    }
    return 0;
}

