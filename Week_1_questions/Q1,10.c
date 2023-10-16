#include "graphics.h"

int main(void)
{
    setWindowSize(1000,500);

    drawLine(100,100,100,450);
    drawLine(75,450,800,450);

    drawLine(100,363,75,363);
    drawLine(100,275,75,275);
    drawLine(100,188,75,188);

    drawString("0",40,450);
    drawString("50",40,363);
    drawString("100",40,275);
    drawString("150",40,188);

    drawString("CDs",150,475);
    drawString("DVDs",300,475);
    drawString("Books",450,475);
    drawString("Clothes",600,475);
    drawString("Shoes",750,475);

    setColour(blue);
    fillRect(100,340,140,110);
    setColour(green);
    fillRect(240,220,140,230);
    setColour(red);
    fillRect(380,280,140,170);
    setColour(yellow);
    fillRect(520,320,140,130);
    setColour(pink);
    fillRect(660,190,140,260);
    return 0;
}