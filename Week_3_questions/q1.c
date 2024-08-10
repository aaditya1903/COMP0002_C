#include<stdio.h>
#include<math.h>

int findPerimeter(int a,int b,int c){
    return a+b+c;
}

int semiPerimeter(int a,int b,int c){
    return 0.5*(a+b+c);
}

int findArea(int a,int b,int c, int s){
    int area = sqrt(s*(s-a)*(s-b)*(s-c));
    return area;
}

int main(){
    int a,b,c;
    printf("Type the side lengths of the triangle: ");
    scanf("%d %d %d", &a,&b,&c);

    int perimeter = findPerimeter(a,b,c);
    int s = semiPerimeter(a,b,c);
    int area = findArea(a,b,c,s);

    printf("Perimeter: %d\tArea: %d\n", perimeter, area);
    return 0;
}