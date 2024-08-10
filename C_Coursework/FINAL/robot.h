#ifndef ROBOT_H
#define ROBOT_H

#include "grid.h"

struct Robot {
    int robotX[3];
    int robotY[3];
    char robotDir;
};

void drawRobot(struct Robot *r);
int canMoveForward(struct Grid *g, struct Robot *r);
void moveForward(struct Robot *r);
void turnLeft(struct Robot *r);
void turnRight(struct Robot *r);
int atMarker(struct Grid *g, struct Robot *r);

#endif // ROBOT_H