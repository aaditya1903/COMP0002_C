#include <stdio.h>

int main()
{
    int rows = 6;
    int columns = 6;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if ((i + j) % 2 == 0)
            {
                printf("*");
            } 
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
    return 0;
}