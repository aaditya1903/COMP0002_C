#include<stdio.h>

int rectangles (int a, int b, char c)
{
    for (int n = 0 ; n < a ; n++)
    {
        for (int m = 0 ; m < b ; m++)
        {
            printf("%c", c);
        }
    printf("\n");
    }
return 0;
}

int main()
{   
    int ret = rectangles(5,5,'&');
    return ret;
}