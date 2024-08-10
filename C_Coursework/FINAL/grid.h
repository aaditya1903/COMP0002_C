#ifndef GRID_H
#define GRID_H

#include "constants.h"

extern int homeX;
extern int homeY;

struct Grid {
    int grid[GRID_SIZE_X][GRID_SIZE_Y];
    int checked[GRID_SIZE_X][GRID_SIZE_Y];
};

void getHomeCoordinates(struct Grid *g);
void initializeGrid(struct Grid *g, int value);
void drawGridLines();
void colourGridSquares(struct Grid *g);
void drawImmovableBlocks(int a, struct Grid *g);
void drawMarker(int a, struct Grid *g);
void drawHome(struct Grid *g);
void drawGrid(struct Grid *g);
void endProgram();

#endif // GRID_H