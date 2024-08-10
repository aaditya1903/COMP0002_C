#include "robot.h"
#include "graphics.h"
#include "grid.h"

void drawRobot(struct Robot *r) {
    foreground();
    setColour(green);
    fillPolygon(3, (*r).robotX, (*r).robotY);
}

void moveForward(struct Robot *r) {
    int increment = 1; // for smoother animation purpose
    int delay = 3;
    foreground();
    switch ((*r).robotDir) {
    case 'n':
        for (int i = 0; i < (SQUARE_SIZE / increment); i++) {
            clear();
            for (int a = 0; a < 3; a++) {
                (*r).robotY[a] -= increment;
            }
            drawRobot(r);
            sleep(delay);
        }
        homeY--; // indexing for grid position, e.g. (0, 0)
        break;
    case 'e':
        for (int i = 0; i < (SQUARE_SIZE / increment); i++) {
            clear();
            for (int a = 0; a < 3; a++) {
                (*r).robotX[a] += increment;
            }
            drawRobot(r);
            sleep(delay);
        }
        homeX++;
        break;
    case 's':
        for (int i = 0; i < (SQUARE_SIZE / increment); i++) {
            clear();
            for (int a = 0; a < 3; a++) {
                (*r).robotY[a] += increment;
            }
            drawRobot(r);
            sleep(delay);
        }
        homeY++;
        break;
    case 'w':
        for (int i = 0; i < (SQUARE_SIZE / increment); i++) {
            clear();
            for (int a = 0; a < 3; a++) {
                (*r).robotX[a] -= increment;
            }
            drawRobot(r);
            sleep(delay);
        }
        homeX--;
        break;
    }
}

int canMoveForward(struct Grid *g, struct Robot *r) {
    int xToCheck, yToCheck, xCell, yCell;
    char robDir = (*r).robotDir;
    switch (robDir) {
    case 'e':
        xToCheck = homeX + 1;
        yToCheck = homeY;
        break;
    case 'n':
        xToCheck = homeX;
        yToCheck = homeY - 1;
        break;
    case 's':
        xToCheck = homeX;
        yToCheck = homeY + 1;
        break;
    case 'w':
        xToCheck = homeX - 1;
        yToCheck = homeY;
        break;
    }
    if (xToCheck < 0 || xToCheck >= GRID_SIZE_X || yToCheck < 0 || yToCheck >= GRID_SIZE_Y) { // checking if robot will be within the grid boundaries
        return 0;
    } else if (g->grid[xToCheck][yToCheck] == 1) { // checking if the block ahead is an immovable block
        return 0;
    } else {
        return 1;
    }
}

void turnLeft(struct Robot *r) {
    foreground();
    clear();
    int tempX[3], tempY[3];
    switch ((*r).robotDir) {
    case 'n':
        for (int i = 0; i < 3; i++) {
            tempX[i] = (*r).robotX[i];
            tempY[i] = (*r).robotY[i];
        }
        (*r).robotDir = 'w';
        (*r).robotX[0] = (tempX[0] - SQUARE_SIZE / 2); // different calculations for each direction
        (*r).robotY[0] = (tempY[0] + SQUARE_SIZE / 2);
        (*r).robotX[1] = (tempX[1] + SQUARE_SIZE);
        (*r).robotY[2] = (tempY[2] - SQUARE_SIZE);
        break;
    case 'e':
        for (int i = 0; i < 3; i++) {
            tempX[i] = (*r).robotX[i];
            tempY[i] = (*r).robotY[i];
        }
        (*r).robotDir = 'n';
        (*r).robotX[0] = (tempX[0] - SQUARE_SIZE / 2);
        (*r).robotY[0] = (tempY[0] - SQUARE_SIZE / 2);
        (*r).robotY[1] = (tempY[1] + SQUARE_SIZE);
        (*r).robotX[2] = (tempX[2] + SQUARE_SIZE);
        break;
    case 's':
        for (int i = 0; i < 3; i++) {
            tempX[i] = (*r).robotX[i];
            tempY[i] = (*r).robotY[i];
        }
        (*r).robotDir = 'e';
        (*r).robotX[0] = (tempX[0] + SQUARE_SIZE / 2);
        (*r).robotY[0] = (tempY[0] - SQUARE_SIZE / 2);
        (*r).robotX[1] = (tempX[1] - SQUARE_SIZE);
        (*r).robotY[2] = (tempY[2] + SQUARE_SIZE);
        break;
    case 'w':
        for (int i = 0; i < 3; i++) {
            tempX[i] = (*r).robotX[i];
            tempY[i] = (*r).robotY[i];
        }
        (*r).robotDir = 's';
        (*r).robotX[0] = (tempX[0] + SQUARE_SIZE / 2);
        (*r).robotY[0] = (tempY[0] + SQUARE_SIZE / 2);
        (*r).robotY[1] = (tempY[1] - SQUARE_SIZE);
        (*r).robotX[2] = (tempX[2] - SQUARE_SIZE);
        break;
    }
    drawRobot(r);
}

void turnRight(struct Robot *r) {
    foreground();
    clear();
    int tempX[3], tempY[3];
    switch ((*r).robotDir) {
    case 'n':
        for (int i = 0; i < 3; i++) {
            tempX[i] = (*r).robotX[i];
            tempY[i] = (*r).robotY[i];
        }
        (*r).robotDir = 'e';
        (*r).robotX[0] = (tempX[0] + SQUARE_SIZE / 2); // different calculations for each direction
        (*r).robotY[0] = (tempY[0] + SQUARE_SIZE / 2);
        (*r).robotY[1] = (tempY[1] - SQUARE_SIZE);
        (*r).robotX[2] = (tempX[2] - SQUARE_SIZE);
        break;
    case 'e':
        for (int i = 0; i < 3; i++) {
            tempX[i] = (*r).robotX[i];
            tempY[i] = (*r).robotY[i];
        }
        (*r).robotDir = 's';
        (*r).robotX[0] = (tempX[0] - SQUARE_SIZE / 2);
        (*r).robotY[0] = (tempY[0] + SQUARE_SIZE / 2);
        (*r).robotX[1] = (tempX[1] + SQUARE_SIZE);
        (*r).robotY[2] = (tempY[2] - SQUARE_SIZE);
        break;
    case 's':
        for (int i = 0; i < 3; i++) {
            tempX[i] = (*r).robotX[i];
            tempY[i] = (*r).robotY[i];
        }
        (*r).robotDir = 'w';
        (*r).robotX[0] = (tempX[0] - SQUARE_SIZE / 2);
        (*r).robotY[0] = (tempY[0] - SQUARE_SIZE / 2);
        (*r).robotY[1] = (tempY[1] + SQUARE_SIZE);
        (*r).robotX[2] = (tempX[2] + SQUARE_SIZE);
        break;
    case 'w':
        for (int i = 0; i < 3; i++) {
            tempX[i] = (*r).robotX[i];
            tempY[i] = (*r).robotY[i];
        }
        (*r).robotDir = 'n';
        (*r).robotX[0] = (tempX[0] + SQUARE_SIZE / 2);
        (*r).robotY[0] = (tempY[0] - SQUARE_SIZE / 2);
        (*r).robotX[1] = (tempX[1] - SQUARE_SIZE);
        (*r).robotY[2] = (tempY[2] + SQUARE_SIZE);
        break;
    }
    drawRobot(r);
}

int atMarker(struct Grid *g, struct Robot *r) {
    int xCell, yCell;
    char robDir = (*r).robotDir;
    switch (robDir) {
    case 'e':
        xCell = ((*r).robotX[0] -  (2*SQUARE_SIZE)) / SQUARE_SIZE; // converting pixel position to grid position
        yCell = ((*r).robotY[0] - SQUARE_SIZE) / SQUARE_SIZE;
        break;
    case 'n':
        xCell = ((*r).robotX[0] -  SQUARE_SIZE) / SQUARE_SIZE;
        yCell = ((*r).robotY[0] - SQUARE_SIZE) / SQUARE_SIZE;
        break;
    case 's':
        xCell = ((*r).robotX[0] -  SQUARE_SIZE) / SQUARE_SIZE;
        yCell = ((*r).robotY[0] - (2*SQUARE_SIZE)) / SQUARE_SIZE;
        break;
    case 'w':
        xCell = ((*r).robotX[0] -  SQUARE_SIZE) / SQUARE_SIZE;
        yCell = ((*r).robotY[0] - SQUARE_SIZE) / SQUARE_SIZE;
        break;
    }
    if (g->grid[xCell][yCell] == 2) {
        return 1;
    } else {
        return 0;
    }
}