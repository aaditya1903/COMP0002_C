#include "grid.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int homeX;
int homeY;

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