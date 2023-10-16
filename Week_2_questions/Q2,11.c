#include<stdio.h>

int main()
{
    printf("Part A\n");
    for (int i = 1; i < 101; i++)
    {
        printf("%i. %i\n", i, i*i);
    }

    printf("\n\n");

    printf("Part B\n");
    int a;
    while (a < 102)
    {
        if (a % 2 == 0){
            printf("%i. %i\n", a, a*a);
            a++;
        }
        else{
            a++;
        }
    }

    printf("\n\n");

    printf("Part C\n");
    int j, count;
    for (int b = 1; b < 101; b++)
    {
        count = 0;
        j = 2;
        while (j <= b/2)
        {
            if (b % j == 0)
            {
                count++;
                break;
            }
            j++;
        }
        if (count == 0 && b != 1)
        {
            printf("%i\n", b);
        }
        b++;
    }
}