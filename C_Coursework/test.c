// including libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graphics.h"

// defining constants
#define GRID_SIZE_X 10
#define GRID_SIZE_Y 10
#define SQUARE_SIZE 50
#define numImmovableBlocks 4

int robotX, robotY;
int immovableBlockX[numImmovableBlocks];
int immovableBlockY[numImmovableBlocks];

// Function declarations
void drawGrid();
void drawImmovableBlocks();
void drawMarker();
void drawHomeAndRobot();

void forward();
void left();
void right();
int atMarker();
int canMoveForward();
int atHome();
void pickUpMarker();
void dropMarker();
int isCarryingAMarker();

int main() {
    setWindowSize((GRID_SIZE_X + 2) * SQUARE_SIZE, (GRID_SIZE_Y + 2) * SQUARE_SIZE);
    srand(time(NULL));
    drawGrid();
    return 0;
}

// Function definitions
void drawGrid() {
    background();
    for (int i = 1; i <= GRID_SIZE_Y + 1; i++) {
        drawLine(SQUARE_SIZE, i * SQUARE_SIZE, (GRID_SIZE_X + 1) * SQUARE_SIZE, i * SQUARE_SIZE);
    }
    for (int i = 1; i <= GRID_SIZE_X + 1; i++) {
        drawLine(i * SQUARE_SIZE, SQUARE_SIZE, i * SQUARE_SIZE, (GRID_SIZE_Y + 1) * SQUARE_SIZE);
    }
    drawImmovableBlocks(numImmovableBlocks);
    drawHomeAndRobot();
    drawMarker();
}

void drawImmovableBlocks() {
    setColour(black);
    for (int i = 0; i < numImmovableBlocks; i++) {
        fillRect((rand() % GRID_SIZE_X) * SQUARE_SIZE + SQUARE_SIZE,
                 (rand() % GRID_SIZE_Y) * SQUARE_SIZE + SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE);
    }
}

void drawMarker() {
    setColour(gray);
    // Place marker against the wall
    fillRect((GRID_SIZE_X + 1) * SQUARE_SIZE - SQUARE_SIZE, (rand() % GRID_SIZE_Y) * SQUARE_SIZE + SQUARE_SIZE,
             SQUARE_SIZE, SQUARE_SIZE);
}

void drawHomeAndRobot() {
    // Home
    setColour(blue);
    int homeX = (rand() % GRID_SIZE_X) * SQUARE_SIZE + SQUARE_SIZE;
    int homeY = (rand() % GRID_SIZE_Y) * SQUARE_SIZE + SQUARE_SIZE;
    fillRect(homeX, homeY, SQUARE_SIZE, SQUARE_SIZE);

    // Robot
    setColour(green);
    int robotX = homeX + SQUARE_SIZE / 2;
    int robotY = homeY + SQUARE_SIZE / 2;
    int robotSize = SQUARE_SIZE / 2;
    int robotPointsX[3] = {robotX, robotX - robotSize, robotX + robotSize};
    int robotPointsY[3] = {robotY - robotSize, robotY + robotSize, robotY + robotSize};
    fillPolygon(3, robotPointsX, robotPointsY);
}

void getRobotPosition(int *x, int *y) {
    // Assuming the robot's position is stored globally or in a structure
    *x = robotX;
    *y = robotY;
}

int collidesWithImmovableBlocks(int x, int y) {
    // Assuming immovable blocks' positions are stored globally or in a structure
    for (int i = 0; i < numImmovableBlocks; i++) {
        int blockX = immovableBlockX[i];
        int blockY = immovableBlockY[i];

        if (x >= blockX && x <= blockX + SQUARE_SIZE && y >= blockY && y <= blockY + SQUARE_SIZE) {
            return 1;
        }
    }
    return 0;
}

int canMoveForward() {
    int robotX, robotY;
    getRobotPosition(&robotX, &robotY);

    int newRobotX = robotX + SQUARE_SIZE;
    int newRobotY = robotY;

    if (newRobotX >= SQUARE_SIZE && newRobotX <= GRID_SIZE_X * SQUARE_SIZE && newRobotY >= SQUARE_SIZE &&
        newRobotY <= GRID_SIZE_Y * SQUARE_SIZE) {

        if (!collidesWithImmovableBlocks(newRobotX, newRobotY))
        {
            return 1;
        }
    }
    return 0;
}


