//Written by Aaditya Kumar on 03/10/2023
//This program displays my name

#include<stdio.h>
#include<string.h>

int main(void)
{
    char myName[] = "Aaditya Kumar";
    printf("My name is %s.\n", myName);

    int index = strlen(myName) - 1;
    while (index > 1)
    {
        printf("%c", myName[index]);
        index-=1;
    }

    printf("\n");
    return 0;
}