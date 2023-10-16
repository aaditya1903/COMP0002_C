#include <stdio.h>

int main(void){
    int n = 1;
    while (n < 11){
        printf("%i * 13 = %i\n", n, n*13);
        n++;
    }
}