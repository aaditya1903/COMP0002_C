#include <stdio.h>

int main(void){
    int n = 1;
    do
    {
        printf("%i * 13 = %i\n", n, n*13);
        n++;
    } while (n<11);
}