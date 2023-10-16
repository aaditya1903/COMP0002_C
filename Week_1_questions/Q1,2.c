//Written by Aaditya Kumar on 03/10/2023
//This program displays my name

#include<stdio.h>
#include<string.h>

int main(void)
{
    char myName[] = "Aaditya Kumar";
    char Address1[] = "Computer Science Department";
    char Address2[] = "University College London";
    char Address3[] = "Gower Street";
    char Address4[] = "London";
    char Address5[] = "WC1E 6BT";

    printf("My name is %s.\n\n", myName);
    printf("The address is: \n%s\n%s\n%s\n%s\n%s\n\n", Address1, Address2, Address3, Address4, Address5);

    int index = strlen(myName) - 1;
    while (index > 1)
    {
        printf("%c", myName[index]);
        index-=1;
    }

    printf("\n");
    return 0;
}