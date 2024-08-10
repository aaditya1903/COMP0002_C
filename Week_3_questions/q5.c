#include <stdio.h>

void units(int num) {
    char* unitName[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    printf("%s", unitName[num]);
}

void tens(int num) {
    if (num < 10) {
        units(num);
    } else if (num < 20) {
        char* teenName[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
        printf("%s", teenName[num - 10]);
    } else {
        char* tenName[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
        printf("%s%s", tenName[num / 10], (num % 10 != 0) ? " " : "");
        units(num % 10);
    }
}

void hundreds(int num) {
    if (num < 100) {
        tens(num);
    } else {
        units(num / 100);
        printf(" hundred");
        if (num % 100 != 0) {
            printf(" and ");
            tens(num % 100);
        }
    }
}

void number(int num) {
    if (num < 0 || num > 999)
    {
        printf("Number not within range (0-999)\n");
    } 
    else if (num == 0)
    {
        printf("zero\n");
    } 
    else
    {
        hundreds(num);
        printf("\n");
    }
}

int main()
{
    int num;
    printf("Please enter an integer between 0 and 999: ");
    scanf("%d", &num);
    number(num);

    return 0;
}
