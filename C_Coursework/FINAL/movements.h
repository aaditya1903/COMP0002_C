#ifndef MOVEMENTS_H
#define MOVEMENTS_H

#include "grid.h"
#include "robot.h"

struct Movement {
    int steps;
    char direction;
};

struct MovementStack {
    struct Movement movements[GRID_SIZE_X * GRID_SIZE_X * GRID_SIZE_X];
    int top;
};

void pushMovement(struct MovementStack *stack, int steps, char direction);
struct Movement popMovement(struct MovementStack *stack);

void findMarker(struct Grid *g, struct Robot *r, struct MovementStack *movements);
void gotMarkerAnimation(struct Grid *g, struct Robot *r);
void returnHome(struct Grid *g, struct Robot *r, struct MovementStack *movements);

#endif // MOVEMENTS_H