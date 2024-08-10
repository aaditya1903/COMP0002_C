#include <stdio.h>

int factorial(int num)
{
    if (num == 0 || num == 1)
    {
        return 1;
    }
    return num * factorial(num - 1);
}

int strong(int num)
{
    int originalNum = num;
    int sum = 0;

    while (num > 0)
    {
        int digit = num % 10;
        sum += factorial(digit);
        num /= 10;
    }

    return (sum == originalNum);
}

void outputStrong(int lowerLimit, int upperLimit)
{
    printf("Strong numbers between %d and %d are:\n", lowerLimit, upperLimit);

    for (int i = lowerLimit; i <= upperLimit; ++i)
    {
        if (strong(i))
        {
            printf("%d\n", i);
        }
    }
}

int main()
{
    int lowerLimit, upperLimit;

    printf("Enter lower limit: ");
    scanf("%d", &lowerLimit);
    printf("Enter upper limit: ");
    scanf("%d", &upperLimit);

    if (lowerLimit >= 0 && lowerLimit <= upperLimit)
    {
        outputStrong(lowerLimit, upperLimit);
    } 
    else
    {
        printf("Error. Invalid range\n");
    }

    return 0;
}
