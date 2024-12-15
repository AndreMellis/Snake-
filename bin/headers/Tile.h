#ifndef TILES_HEADER_
#define TILES_HEADER_

#define TILE_WIDTH 10
#define TILE_HEIGHT 10

#include <SDL.h>
#include "WindowRendering.h"

class Tile
{
private:
    WindowRendering *pWindowRenderer = WindowRendering::getInstance();

    bool occupied;
    SDL_Rect cords;

public:
    Tile(int x, int y); // constructor takes in an x and y for cords

    bool isOccupied() { return occupied; }
    void toggleOccupied(); //removes or add snake depending on occupied

    void render(); // if you have a snake, print it
    SDL_Rect *getCords() { return &cords; }
};

#endif