// including libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graphics.h"

// defining constants
#define GRID_SIZE_X 10
#define GRID_SIZE_Y 10
#define SQUARE_SIZE 50
// #define NUM_IMMOVABLE_BLOCKS 5

// function declerations
void drawGrid();
void drawImmovableBlocks(int a);
void drawMarker();
void drawHome();
void drawRobot();

void forward();
void left();
void right();
int atMarker();
int canMoveForward();
int atHome();
void pickUpMarker();
void dropMarker();
int isCarryingAMarker();

int main()
{
    setWindowSize((GRID_SIZE_X + 2) * SQUARE_SIZE, (GRID_SIZE_Y + 2) * SQUARE_SIZE); // can be 2 or any other number
    srand(time(NULL));
    drawGrid();
    return 0;
}

// function definitions
void drawGrid()
{
    background();
    for (int i = 1; i <= GRID_SIZE_Y + 1; i++) // n rows means n+1 lines
    {
        drawLine(SQUARE_SIZE, i * SQUARE_SIZE, (GRID_SIZE_X + 1) * SQUARE_SIZE, i * SQUARE_SIZE);
    }
    for (int i = 1; i <= GRID_SIZE_X + 1; i++) // n columns meansn n+1 lines
    {
        drawLine(i * SQUARE_SIZE, SQUARE_SIZE, i * SQUARE_SIZE, (GRID_SIZE_Y + 1) * SQUARE_SIZE);
    }
    int NumImmovableBlocks = 4;
    int homeX, homeY;
    drawImmovableBlocks(NumImmovableBlocks);
    drawMarker();
    drawHome(&homeX, &homeY);
    drawRobot(homeX, homeY);
}

void drawImmovableBlocks(int a)
{
    background();
    setColour(black);
    for (int i = 0; i < a; i++)
    {
        fillRect((rand() % GRID_SIZE_X) * SQUARE_SIZE + SQUARE_SIZE, (rand() % GRID_SIZE_Y) * SQUARE_SIZE + SQUARE_SIZE,
                 SQUARE_SIZE, SQUARE_SIZE); // modulus used to ensure coloured squares aligns exactly with grid square
    }
}

void drawMarker()
{
    background();
    setColour(gray);
    fillRect((rand() % GRID_SIZE_X) * SQUARE_SIZE + SQUARE_SIZE, (rand() % GRID_SIZE_Y) * SQUARE_SIZE + SQUARE_SIZE,
             SQUARE_SIZE, SQUARE_SIZE); // modulus used to ensure coloured square aligns exactly with grid square
}

void drawHome(int *homeX, int *homeY)
{
    background();
    setColour(blue);
    *homeX = (rand() % GRID_SIZE_X) * SQUARE_SIZE + SQUARE_SIZE;
    *homeY = (rand() % GRID_SIZE_Y) * SQUARE_SIZE + SQUARE_SIZE;
    fillRect(*homeX, *homeY, SQUARE_SIZE, SQUARE_SIZE);
}

void drawRobot(int homeX, int homeY)
{
    setColour(green);
    int robotX = homeX + SQUARE_SIZE / 2;
    int robotY = homeY + SQUARE_SIZE / 2;
    int robotSize = SQUARE_SIZE / 2;
    int robotPointsX[3] = {robotX, robotX - robotSize, robotX + robotSize};
    int robotPointsY[3] = {robotY - robotSize, robotY + robotSize, robotY + robotSize};
    fillPolygon(3, robotPointsX, robotPointsY);
}
