#include<stdio.h>

int main() {
    int row = 9;
    int col = 5;
    for (int i = 0; i < row; i++)
    {
        if (i < row / 2) {
            for (int j = 0; j < i; j++)
            {
                printf(" ");
            }
        } 
        else
        {
            for (int j = 0; j < row - i - 1; j++)
            {
                printf(" ");
            }
        }
        for (int k = 0; k < col; k++) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}