#include<stdio.h>

int prime(long a)
{
    int number, tof = 1;
    
    for (number = 2; number <= a / 2; number++)
    {
        if (a % number == 0)
        {
            tof = 0;
            break;
        }
    }
    return tof;
}

int main()
{
    long num;
    
    printf("Please enter a number: ");
    scanf("%ld",&num);

    int result = prime(num);

    if (result == 1)
    {
        printf("The entered value is prime.\n");
    }
    else
    {
        printf("The entered value is not prime.\n");
    }

    return 0;
}