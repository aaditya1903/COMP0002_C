#include <stdio.h>

int main()
{
    int hrs, mins;
    printf("Enter time in 24-hour format: ");
    scanf("%d:%d", &hrs, &mins);
    
    if (hrs >= 0 && hrs <= 23 && mins >= 0 && mins <= 59)
    {
        if (hrs == 0)
        {
            printf("12:%.2d am\n", mins);
        } 
        else if (hrs < 12)
        {
            printf("%.2d:%.2d am\n", hrs, mins);
        }
        else if (hrs == 12)
        {
            printf("12:%.2d pm\n", mins);
        }
        else
        {
            printf("%.2d:%.2d pm\n", hrs - 12, mins);
        }
    }
    else
    {
        printf("Invalid time inputted.\n");
    }

    return 0;
}
