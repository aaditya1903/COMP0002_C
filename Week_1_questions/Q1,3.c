#include "graphics.h"

int main(void)
{
    drawLine(60,25,110,25);
    drawLine(110,25,145,60);
    drawLine(145,60,145,110);
    drawLine(145,110,110,145);
    drawLine(110,145,60,145);
    drawLine(60,145,25,110);
    drawLine(25,110,25,60);
    drawLine(25,60,60,25);
    return 0;
}

/*
int main(void)
{
 setWindowSize(800, 800);

 double line_length = 100;
 int i;
 const long double pi = 4.0 * atan(1.0);
 double last_x = 200;
 double last_y = 200;
 double angle_increment = (2*pi)/4;
 double angle = 0;

 for (i = 0; i < 4; i++) {
  double next_x = last_x + line_length * cos(angle);
  double next_y = last_y + line_length * sin(angle);
  drawLine(last_x, last_y, next_x, next_y);

  last_x = next_x;
  last_y = next_y;
  angle = angle + angle_increment;
}
 return 0;
}
*/