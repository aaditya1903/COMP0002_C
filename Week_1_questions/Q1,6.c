#include "graphics.h"
#include<math.h>

int main(void)
{
    drawArc(50,50,50,50,0,360);
    int x = 50 + (sqrt(312.5)/2); //(50,50) was starting coordinate which is why we add 50
    int width = sqrt(50*50/2);
    drawRect(x,x,width,width);
    return 0;
}