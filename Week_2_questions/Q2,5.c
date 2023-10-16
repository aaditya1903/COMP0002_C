#include<stdio.h>

/*int main()
{
    for (int row = 6; row > 0; row--)
    {
        int col = row;
        while (col > 0)
        {
            printf("*");
            col--;
        }
        printf("\n");
    }
}*/

int main() 
{
  int row = 6;
  for (int i = 1; i <= row; i++)
  {
    printf("\n");
    for (int j = 1; j <= i; j++)
    {
      printf(" ");
    }
    for (int k = 1; k <= (row + 1 - i); k++)
    {
      printf("*");
    }
  }
    return 0;
}

