#include "graphics.h"
#include <math.h>

void drawBackground()
{
    background();
    setColour(green);
    fillArc(300, 300, 300, 300, 0, 360);
    setColour(white);
    fillArc(325, 325, 250, 250, 0, 360);
}

void drawSquare(double x, double y)
{
    foreground();
    setColour(blue);
    int sideLength = 50;
    // adjusting the starting point so that the square aligns with the doughnut circumference
    fillRect(x - (sideLength / 2), y - (sideLength / 2), sideLength, sideLength);
}

void moveSquare()
{
    foreground();
    double center = 450;
    double radius = 150;
    double angle = 0;

    while (1)
    {
        double x = center + radius * cos(angle);
        double y = center + radius * sin(angle);

        clear();
        drawSquare(x, y);

        angle += 0.01;

        sleep(10);
    }
}

int main(void)
{
    setWindowSize(1000, 1000);
    drawBackground();
    moveSquare();

    return 0;
}
