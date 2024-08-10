// including libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "graphics.h"

// defining constants
#define GRID_SIZE_X 10
#define GRID_SIZE_Y 10
#define SQUARE_SIZE 50
#define IMMOVABLE_BLOCK_COUNT 2
#define MARKER_COUNT 2

int homeX;
int homeY;

struct Grid {
    int grid[GRID_SIZE_X][GRID_SIZE_Y];
    int checked[GRID_SIZE_X][GRID_SIZE_Y];
};

struct Robot {
    int robotX[3];
    int robotY[3];
    char robotDir;
};

struct Movement {
    int steps;
    char direction;
};

struct MovementStack {
    struct Movement movements[GRID_SIZE_X * GRID_SIZE_X * GRID_SIZE_X];
    int top;
};

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

// declaring functions
void initializeGrid(struct Grid *g, int value);
void drawGridLines();
void drawGrid(struct Grid *g);
void drawImmovableBlocks(int a, struct Grid *g);
void drawMarker(int a, struct Grid *g);
void drawHome(struct Grid *g);
void drawRobot(struct Robot *r);
int canMoveForward(struct Grid *g, struct Robot *r);
void moveForward(struct Robot *r);
void turnLeft(struct Robot *r);
void turnRight(struct Robot *r);
int atMarker(struct Grid *g, struct Robot *r);
void findMarker(struct Grid *g, struct Robot *r, struct MovementStack *movements);
void returnHome(struct Grid *g, struct Robot *r, struct MovementStack *movements);

void getHomeCoordinates(struct Grid *g) {
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            if (g->grid[i][j] == 3) { // home is initialised to '3'
                homeX = i;
                homeY = j;
                break;
            }
        }
    }
}

void endProgram() {
    background();
    clear();
    foreground();
    clear();
    setColour(black);
    drawString("Found all markers successfully.", ((GRID_SIZE_X - 2) * SQUARE_SIZE) / 2, ((GRID_SIZE_Y + 2) * SQUARE_SIZE) / 2);
}

int main() {
    srand(time(NULL)); // randomising block positions each time the code in run
    struct Grid myGrid;
    drawGrid(&myGrid);
    getHomeCoordinates(&myGrid);
    struct Robot myRobot = {
        {(homeX + 1.5) * SQUARE_SIZE, (homeX + 1) * SQUARE_SIZE, (homeX + 2) * SQUARE_SIZE}, // calculating robot vertices based on top left corner
        {(homeY + 1) * SQUARE_SIZE, (homeY + 2) * SQUARE_SIZE, (homeY + 2) * SQUARE_SIZE}, // calculating robot vertices based on top left corner
        'n'
    }; // making sure the robot's initial position is directly on top of the home square
    struct MovementStack movements;
    movements.top = -1;
    drawRobot(&myRobot);
    sleep(1000);
    for (int i = 0; i < MARKER_COUNT; i++) {
        findMarker(&myGrid, &myRobot, &movements);
        sleep(1000);
        returnHome(&myGrid, &myRobot, &movements);
        sleep(1000);
    }
    endProgram();
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
    for (int i = 0; i <= GRID_SIZE_X; i++) {
        drawLine((i + 1) * SQUARE_SIZE, SQUARE_SIZE, (i + 1) * SQUARE_SIZE, (GRID_SIZE_Y + 1) * SQUARE_SIZE); // n columns = n+1 lines
    }
    for (int i = 0; i <= GRID_SIZE_Y; i++) {
        drawLine(SQUARE_SIZE, (i + 1) * SQUARE_SIZE, (GRID_SIZE_X + 1) * SQUARE_SIZE, (i + 1) * SQUARE_SIZE); // n rows = n+1 lines
    }
}

void colourGridSquares (struct Grid *g) {
    for (int i = 0; i < GRID_SIZE_X; i++) {
        for (int j = 0; j < GRID_SIZE_Y; j++) {
            int x = (i + 1) * SQUARE_SIZE;
            int y = (j + 1) * SQUARE_SIZE;
            if (g->grid[i][j] == 1) { // Immovable block
                setColour(black);
                fillRect(x, y, SQUARE_SIZE, SQUARE_SIZE);
            } else if (g->grid[i][j] == 2) { // Marker
                setColour(gray);
                fillRect(x, y, SQUARE_SIZE, SQUARE_SIZE);
            } else if (g->grid[i][j] == 3) { // Home
                setColour(blue);
                fillRect(x, y, SQUARE_SIZE, SQUARE_SIZE);
            }
        }
    }
}

void drawGrid(struct Grid *g) {
    setWindowSize((GRID_SIZE_X + 2) * SQUARE_SIZE, (GRID_SIZE_Y + 2) * SQUARE_SIZE);
    background();
    initializeGrid(g, 0);
    drawGridLines();
    drawImmovableBlocks(IMMOVABLE_BLOCK_COUNT, g);
    drawMarker(MARKER_COUNT, g);
    drawHome(g);
    colourGridSquares(g);
}

void drawImmovableBlocks(int a, struct Grid *g) {
    for (int k = 0; k < a; k++) {
        int x, y;
        do {
            x = rand() % GRID_SIZE_X;
            y = rand() % GRID_SIZE_Y;
        } while (g->grid[x][y] != 0);
        g->grid[x][y] = 1;
    }
}

void drawMarker(int a, struct Grid *g) {
    int x, y;
    for (int i = 0; i < a; i++) {
        do {
            x = rand() % GRID_SIZE_X;
            y = rand() % GRID_SIZE_Y;
        } while (g->grid[x][y] != 0);
        g->grid[x][y] = 2;
    }
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
