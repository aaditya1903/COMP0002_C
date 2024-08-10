#include<stdio.h>
#include<math.h>

int powerLoop(int x, int y)
{
    int ans = 1;
    for (int a = 1; a <= y; a++)
    {
        ans = x * ans;
    }

    return ans;
}

int powerRecursion(int x, int y)
{

    if (y!=0)
    {
        return x * powerRecursion(x, y-1);
    }

    return 1;
}

int main()
{
    int x,y;
    printf("Enter x and y: ");
    scanf("%d %d", &x, &y);
    int answerLoop = powerLoop(x,y);
    int answerRecursion = powerRecursion(x,y);
    printf("x^y = %d\n",answerLoop);
    printf("x^y = %d\n",answerRecursion);
    return 0;
}