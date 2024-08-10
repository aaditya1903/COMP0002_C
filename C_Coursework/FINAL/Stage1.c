#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "graphics.h"

#define GRID_SIZE_X 10
#define GRID_SIZE_Y 10
#define SQUARE_SIZE 50

int homeX;
int homeY;

struct Grid {
    int grid[GRID_SIZE_X][GRID_SIZE_Y];
};

struct Robot {
    int robotX[3];
    int robotY[3];
    char robotDir;
};

void initializeGrid(struct Grid *g, int value);
void drawGridLines();
void drawGrid(struct Grid *g);
void drawMarker(struct Grid *g);
void drawHome(struct Grid *g);
void drawRobot(struct Robot *r);
int canMoveForward(struct Grid *g, struct Robot *r);
void moveForward(struct Robot *r);
void turnLeft(struct Robot *r);
void turnRight(struct Robot *r);
int atMarker(struct Grid *g, struct Robot *r);
void findMarker(struct Grid *g, struct Robot *r);

void findHomeCoordinates(struct Grid *g, int *homeX, int *homeY) {
    *homeX = -1;
    *homeY = -1;

    for (int i = 0; i < GRID_SIZE_X && *homeX == -1; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            if (g->grid[i][j] == 3) { // home
                *homeX = i;
                *homeY = j;
                break;
            }
        }
    }
}

int main() {
    srand(time(NULL));
    struct Grid myGrid;
    drawGrid(&myGrid);

    int homeX, homeY;
    findHomeCoordinates(&myGrid, &homeX, &homeY);

    struct Robot myRobot = {
        {(homeX + 1.5) * SQUARE_SIZE, (homeX + 1) * SQUARE_SIZE, (homeX + 2) * SQUARE_SIZE},
        {(homeY + 1) * SQUARE_SIZE, (homeY + 2) * SQUARE_SIZE, (homeY + 2) * SQUARE_SIZE},
        'n'
    };

    drawRobot(&myRobot);
    findMarker(&myGrid, &myRobot);
    return 0;
}

void initializeGrid(struct Grid *g, int value) {
    for (int i = 0; i < GRID_SIZE_X; ++i) {
        for (int j = 0; j < GRID_SIZE_Y; ++j) {
            g->grid[i][j] = value;
        }
    }
}

void drawGridLines() {
    for (int i = 0; i <= GRID_SIZE_X; i++)
        drawLine((i + 1) * SQUARE_SIZE, SQUARE_SIZE, (i + 1) * SQUARE_SIZE, (GRID_SIZE_Y + 1) * SQUARE_SIZE);

    for (int i = 0; i <= GRID_SIZE_Y; i++)
        drawLine(SQUARE_SIZE, (i + 1) * SQUARE_SIZE, (GRID_SIZE_X + 1) * SQUARE_SIZE, (i + 1) * SQUARE_SIZE);
}

void drawGrid(struct Grid *g) {
    setWindowSize((GRID_SIZE_X + 2) * SQUARE_SIZE, (GRID_SIZE_Y + 2) * SQUARE_SIZE);
    background();
    initializeGrid(g, 0);
    drawGridLines();
    drawMarker(g);
    drawHome(g);

    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            int x = (i + 1) * SQUARE_SIZE;
            int y = (j + 1) * SQUARE_SIZE;
            int color = ((g->grid[i][j] == 2) ? gray : ((g->grid[i][j] == 3) ? blue : -1));

            if (color != -1) {
                setColour(color);
                fillRect(x, y, SQUARE_SIZE, SQUARE_SIZE);
            }
        }
    }
}

void drawMarker(struct Grid *g) {
    int x, y;
    if (rand() % 2 == 0) {
        x = rand() % GRID_SIZE_X;
        y = (rand() % 2 == 0) ? 0 : GRID_SIZE_Y - 1;
    } else {
        x = (rand() % 2 == 0) ? 0 : GRID_SIZE_X - 1;
        y = rand() % GRID_SIZE_Y;
    }

    while (g->grid[x][y] != 0)
        if (rand() % 2 == 0)
            x = rand() % GRID_SIZE_X, y = (rand() % 2 == 0) ? 0 : GRID_SIZE_Y - 1;
        else
            x = (rand() % 2 == 0) ? 0 : GRID_SIZE_X - 1, y = rand() % GRID_SIZE_Y;

    g->grid[x][y] = 2;
}

void drawHome(struct Grid *g) {
    int x, y;
    do {
        x = rand() % GRID_SIZE_X;
        y = rand() % GRID_SIZE_Y;
    } while (g->grid[x][y] != 0);

    g->grid[x][y] = 3;
}

void drawRobot(struct Robot *r) {
    foreground();
    setColour(green);
    fillPolygon(3, (*r).robotX, (*r).robotY);
}

void moveForward(struct Robot *r) {
    int increment = 1;
    int delay = 5;

    foreground();

    for (int i = 0; i < (SQUARE_SIZE / increment); i++) {
        clear();
        for (int a = 0; a < 3; a++)
            (*r).robotX[a] += (r->robotDir == 'e') ? increment : ((r->robotDir == 'w') ? -increment : 0),
            (*r).robotY[a] += (r->robotDir == 's') ? increment : ((r->robotDir == 'n') ? -increment : 0);

        drawRobot(r);
        sleep(delay);
    }
}

int canMoveForward(struct Grid *g, struct Robot *r) {
    int xToCheck, yToCheck, xCell, yCell;
    char robDir = (*r).robotDir;

    switch (robDir) {
        case 'e':
            xCell = ((*r).robotX[0] -  (2*SQUARE_SIZE)) / SQUARE_SIZE;
            yCell = ((*r).robotY[0] - SQUARE_SIZE) / SQUARE_SIZE;
            xToCheck = xCell + 1;
            yToCheck = yCell;
            break;
        case 'n':
            xCell = ((*r).robotX[0] -  SQUARE_SIZE) / SQUARE_SIZE;
            yCell = ((*r).robotY[0] - SQUARE_SIZE) / SQUARE_SIZE;
            xToCheck = xCell;
            yToCheck = yCell - 1;
            break;
        case 's':
            xCell = ((*r).robotX[0] -  SQUARE_SIZE) / SQUARE_SIZE;
            yCell = ((*r).robotY[0] - (2*SQUARE_SIZE)) / SQUARE_SIZE;
            xToCheck = xCell;
            yToCheck = yCell + 1;
            break;
        case 'w':
            xCell = ((*r).robotX[0] -  SQUARE_SIZE) / SQUARE_SIZE;
            yCell = ((*r).robotY[0] - SQUARE_SIZE) / SQUARE_SIZE;
            xToCheck = xCell - 1;
            yToCheck = yCell;
            break;
    }

    return (xToCheck < 0 || xToCheck >= GRID_SIZE_X || yToCheck < 0 || yToCheck >= GRID_SIZE_Y) ? 0 : 1;
}

void turnLeft(struct Robot *r) {
    foreground();
    clear();
    int tempX[3], tempY[3];
    switch ((*r).robotDir) {
        case 'n':
            for (int i = 0; i < 3; i++)
                tempX[i] = (*r).robotX[i], tempY[i] = (*r).robotY[i];
            (*r).robotDir = 'w';
            (*r).robotX[0] = (tempX[0] - SQUARE_SIZE / 2);
            (*r).robotY[0] = (tempY[0] + SQUARE_SIZE / 2);
            (*r).robotX[1] = (tempX[1] + SQUARE_SIZE);
            (*r).robotY[2] = (tempY[2] - SQUARE_SIZE);
            break;
        case 'e':
            for (int i = 0; i < 3; i++)
                tempX[i] = (*r).robotX[i], tempY[i] = (*r).robotY[i];
            (*r).robotDir = 'n';
            (*r).robotX[0] = (tempX[0] - SQUARE_SIZE / 2);
            (*r).robotY[0] = (tempY[0] - SQUARE_SIZE / 2);
            (*r).robotY[1] = (tempY[1] + SQUARE_SIZE);
            (*r).robotX[2] = (tempX[2] + SQUARE_SIZE);
            break;
        case 's':
            for (int i = 0; i < 3; i++)
                tempX[i] = (*r).robotX[i], tempY[i] = (*r).robotY[i];
            (*r).robotDir = 'e';
            (*r).robotX[0] = (tempX[0] + SQUARE_SIZE / 2);
            (*r).robotY[0] = (tempY[0] - SQUARE_SIZE / 2);
            (*r).robotX[1] = (tempX[1] - SQUARE_SIZE);
            (*r).robotY[2] = (tempY[2] + SQUARE_SIZE);
            break;
        case 'w':
            for (int i = 0; i < 3; i++)
                tempX[i] = (*r).robotX[i], tempY[i] = (*r).robotY[i];
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
            for (int i = 0; i < 3; i++)
                tempX[i] = (*r).robotX[i], tempY[i] = (*r).robotY[i];
            (*r).robotDir = 'e';
            (*r).robotX[0] = (tempX[0] + SQUARE_SIZE / 2);
            (*r).robotY[0] = (tempY[0] + SQUARE_SIZE / 2);
            (*r).robotY[1] = (tempY[1] - SQUARE_SIZE);
            (*r).robotX[2] = (tempX[2] - SQUARE_SIZE);
            break;
        case 'e':
            for (int i = 0; i < 3; i++)
                tempX[i] = (*r).robotX[i], tempY[i] = (*r).robotY[i];
            (*r).robotDir = 's';
            (*r).robotX[0] = (tempX[0] - SQUARE_SIZE / 2);
            (*r).robotY[0] = (tempY[0] + SQUARE_SIZE / 2);
            (*r).robotX[1] = (tempX[1] + SQUARE_SIZE);
            (*r).robotY[2] = (tempY[2] - SQUARE_SIZE);
            break;
        case 's':
            for (int i = 0; i < 3; i++)
                tempX[i] = (*r).robotX[i], tempY[i] = (*r).robotY[i];
            (*r).robotDir = 'w';
            (*r).robotX[0] = (tempX[0] - SQUARE_SIZE / 2);
            (*r).robotY[0] = (tempY[0] - SQUARE_SIZE / 2);
            (*r).robotY[1] = (tempY[1] + SQUARE_SIZE);
            (*r).robotX[2] = (tempX[2] + SQUARE_SIZE);
            break;
        case 'w':
            for (int i = 0; i < 3; i++)
                tempX[i] = (*r).robotX[i], tempY[i] = (*r).robotY[i];
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
        case 'n':
        case 'w':
            xCell = ((*r).robotX[0] -  SQUARE_SIZE) / SQUARE_SIZE;
            yCell = ((*r).robotY[0] - SQUARE_SIZE) / SQUARE_SIZE;
            break;
        case 'e':
            xCell = ((*r).robotX[0] -  (2*SQUARE_SIZE)) / SQUARE_SIZE;
            yCell = ((*r).robotY[0] - SQUARE_SIZE) / SQUARE_SIZE;
            break;
        case 's':
            xCell = ((*r).robotX[0] -  SQUARE_SIZE) / SQUARE_SIZE;
            yCell = ((*r).robotY[0] - (2*SQUARE_SIZE)) / SQUARE_SIZE;
            break;
    }

    return (g->grid[xCell][yCell] == 2);
}

void findMarker(struct Grid *g, struct Robot *r) {
    while (!atMarker(g, r))
        if (canMoveForward(g, r))
            moveForward(r);
        else
            turnRight(r);
}





