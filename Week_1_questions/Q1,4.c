#include "graphics.h"
#include <math.h>

int main(void)
{
 setWindowSize(800, 800);
 
 const long double pi = 4.0 * atan(1.0);

 double line_length = 100;

 double last_x = 200;
 double last_y = 200;

 double angle_increment = (2*pi)/7;
 double angle = 0;

 for (int i = 0; i < 7; i++) {
  double next_x = last_x + line_length * cos(angle);
  double next_y = last_y + line_length * sin(angle);

  drawLine(last_x, last_y, next_x, next_y);

  last_x = next_x;
  last_y = next_y;
  angle = angle + angle_increment;
}
 return 0;
}