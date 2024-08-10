#include <stdio.h>

int isPalindrome(long num)
{
    long og = num;
    long reverse = 0;

    while (num > 0)
    {
        reverse = reverse * 10 + num % 10;
        num /= 10;
    }

    return (og == reverse);
}

int main() {
    long num;

    printf("Enter an integer: ");
    scanf("%ld", &num);

    if (isPalindrome(num))
    {
        printf("%ld is a palindrome.\n", num);
    } 
    else
    {
        printf("%ld is not a palindrome.\n", num);
    }

    return 0;
}