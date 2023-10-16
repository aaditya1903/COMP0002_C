#include "graphics.h"
#include <math.h>

int main(void) {
    setWindowSize(800, 800);

    drawLine(0, 400, 800, 400);  // Horizontal line (x-axis)
    drawLine(360, 0, 360, 800);  // Vertical line (y-axis): why 360?

    float angle, radius = 50;

    for (int i = 0; i < 800; i++) {
        angle = i * (M_PI / 180);
        float initial_sinval = sin(angle);
        float next_sinval = sin((i + 1) * (M_PI / 180));

        // Calculating the y-coordinates
        int initial_yco = 400 - initial_sinval * radius;
        int next_yco = 400 - next_sinval * radius;

        drawLine(i, initial_yco, i + 1, next_yco);
    }
    return 0;
}
