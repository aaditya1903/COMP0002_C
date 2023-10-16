#include "graphics.h"
#include <math.h>

void drawFractal(int x1, int y1, int x2, int y2, int depth)
{
    if (depth == 0)
    {
        drawLine(x1, y1, x2, y2);
        return;
    }

    //intermediate points (split line into 3 parts)
    int x3 = (2 * x1 + x2) / 3;
    int y3 = (2 * y1 + y2) / 3;
    int x4 = (x1 + 2 * x2) / 3;
    int y4 = (y1 + 2 * y2) / 3;

    double angle = 60;

    //calculating new (x,y) by rotating 60˚ around the midpoint (x3,y3)
    int x = x3 + (x4 - x3) * cos(angle * M_PI / 180) - (y4 - y3) * sin(angle * M_PI / 180);
    int y = y3 + (x4 - x3) * sin(angle * M_PI / 180) + (y4 - y3) * cos(angle * M_PI / 180);

    //recursively calling the drawFractal function for each pair of x and y (reducing depth)
    drawFractal(x1, y1, x3, y3, depth - 1);
    drawFractal(x3, y3, x, y, depth - 1);
    drawFractal(x, y, x4, y4, depth - 1);
    drawFractal(x4, y4, x2, y2, depth - 1);
}

int main()
{
    setWindowSize(800, 800);

    int startX = 100, startY = 400, endX = 300, endY = 400, midX = 200, midY = 100;

    int newDepth = 4;

    drawFractal(startX, startY, endX, endY, newDepth);
    drawFractal(endX, endY, midX, midY, newDepth);
    drawFractal(midX, midY, startX, startY, newDepth);

    return 0;
}