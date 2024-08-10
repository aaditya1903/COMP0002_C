#include "movements.h"
#include "graphics.h"
#include "grid.h"

void pushMovement(struct MovementStack *stack, int steps, char direction) {
    stack->top++;
    stack->movements[stack->top].steps = steps;
    stack->movements[stack->top].direction = direction;
}

struct Movement popMovement(struct MovementStack *stack) {
    struct Movement movement = stack->movements[stack->top];
    stack->top--;
    return movement;
}

void collectedMarkerAnimation(struct Grid *g, struct Robot *r) {
    g->grid[homeX][homeY] = 0; // change from marker to empty
    background();
    setColour(white);
    fillPolygon(3, (*r).robotX, (*r).robotY);
    setColour(black);
    drawLine((*r).robotX[1],(*r).robotY[1],(*r).robotX[2],(*r).robotY[2]);
}

void getToCorner(struct Grid *g, struct Robot *r, struct MovementStack *movements) {
    if (!atMarker(g, r)) {
        for (int i = 0; i < 2; i++)
        {
            while (canMoveForward(g, r)) {
                moveForward(r);
                pushMovement(movements, 1, 'F');
                if (atMarker(g, r)) {
                    break;
                }
            }
            turnRight(r);
            pushMovement(movements, 1, 'R');
        }
    }
}

void turnRightAndMove(struct Grid *g, struct Robot *r, struct MovementStack *movements) {
    turnRight(r);
    pushMovement(movements, 1, 'R');
    if (canMoveForward(g, r)) {
        moveForward(r);
        pushMovement(movements, 1, 'F');
    }
    turnRight(r);
    pushMovement(movements, 1, 'R');
}

void turnLeftAndMove(struct Grid *g, struct Robot *r, struct MovementStack *movements) {
    turnLeft(r);
    pushMovement(movements, 1, 'L');
    if (canMoveForward(g, r)) {
        moveForward(r);
        pushMovement(movements, 1, 'F');
    }
    turnLeft(r);
    pushMovement(movements, 1, 'L');
}

int findMarkerCase2(struct Grid *g, struct Robot *r, struct MovementStack *movements) {
    int flag = 1;
    int iterations = 0;
    int maxIterations = 150; 
    turnLeft(r);
    pushMovement(movements, 1, 'L');
    while (!atMarker(g, r)) {
        if (canMoveForward(g, r)) {
            moveForward(r);
            pushMovement(movements, 1, 'F');
        } else if (flag == 1) {
            turnLeftAndMove(g, r, movements);
            flag = 0;
        } else {
            turnRightAndMove(g, r, movements);
            flag = 1;
        }
        iterations++;
        if (iterations > maxIterations) { // in case robot gets stuck in a loop
            break;
        }
    }
    if (iterations > maxIterations) {
        flag = -1;
    }
    return flag;
}

void findMarker(struct Grid *g, struct Robot *r, struct MovementStack *movements) {
    int flag = 1;
    getToCorner(g, r, movements);
    while (!atMarker(g, r)) {
        if (canMoveForward(g, r)) {
            moveForward(r);
            pushMovement(movements, 1, 'F');
        } else if (flag == 1) {
            turnRightAndMove(g, r, movements);
            flag = 0;
        } else if ((homeX == 0 && homeY == 0) || (homeX == 9 && homeY == 9) || (homeX == 0 && homeY == 9) || (homeX == 9 && homeY == 0)) { // robot reaches one of the corners
            flag = findMarkerCase2(g, r, movements);
        } else {
            turnLeftAndMove(g, r, movements);
            flag = 1;
        }
    }
    collectedMarkerAnimation(g, r);
}

void returnHome(struct Grid *g, struct Robot *r, struct MovementStack *movements) {
    turnLeft(r);
    turnLeft(r); // turn 180
    while (movements->top >= 0) { // backtracking moves back to home square
        struct Movement movement = popMovement(movements);
        int steps = movement.steps;
        char direction = movement.direction;
        if (direction == 'F') {
            for (int i = 0; i < steps; i++) {
                moveForward(r);
            }
        } else if (direction == 'R') {
            for (int i = 0; i < steps; i++) {
                turnLeft(r);
            }
        } else if (direction == 'L') {
            for (int i = 0; i < steps; i++) {
                turnRight(r);
            }
        }
    }
}