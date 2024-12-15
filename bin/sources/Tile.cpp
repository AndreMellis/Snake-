#include "Tile.h"

Tile::Tile(int x, int y)
{
    occupied = 0;

    cords.x = x;
    cords.y = y;
    cords.w = TILE_WIDTH;
    cords.h = TILE_HEIGHT;
}

void Tile::toggleOccupied()
{
    if (occupied)
    {
        occupied = 0;
    } else
    {
        occupied = 1;
    }
}

void Tile::render()
{
    if(occupied)
    {
        pWindowRenderer->drawSolidRect(&cords);
    }
}