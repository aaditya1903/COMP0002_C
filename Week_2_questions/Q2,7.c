#include <stdio.h>

int main() {
    int row = 7;
    int col = 8;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (i == 0 || i == row - 1 || j == 0 || j == col - 1)
            {
                printf("*");
            } 
            else if ((i == 2 || i == row - 3) && (j >= 2 && j <= 5))
            {
                printf("#");
            } 
            else if ((i > 2 && i < row - 3) && (j == 2 || j == col - 3))
            {
                printf("#");
            } else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}




