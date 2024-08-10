#include<stdio.h>

int consecProduct(int a, int b)
{
    int ans = 1;
    int A = a-1;
    for (int i = A; i != b; i++)
    {
        ans = ans * a;
        a += 1;
    }
    return ans;
}
int main()
{
    int lolim, uplim;
    printf("Enter lower and upper limit: ");
    scanf("%d %d", &lolim, &uplim);
    int product = consecProduct(lolim, uplim);
    printf("The product is %d\n", product);
}