#ifndef SNAKEGAME_HEADER_
#define SNAKEGAME_HEADER_

#include "Tile.h"
#include "WindowRendering.h"
#include "Score.h"

#include <vector>
#include <utility>
#include <cstdlib>
#include <SDL.h>

class SnakeGame
{
private:
    WindowRendering *pWindowRenderer = WindowRendering::getInstance();
    Score score;

    std::vector<std::vector<Tile*>> mainMap; //mainMap is a 2d vector of ptrs to tiles
    std::vector< std::pair<int,int> > snakeParts; // a vector of pairs holding snake part's Yx cords

    SDL_Rect scoreBoard = {0, 0, 250, 50};

    int mPosY; // head's y pos
    int mPosX; // head's x pos

    int mVelY; // head's y vel
    int mVelX; // head's x vel

    int dotY;
    int dotX;

    int tileWidthCount; // these are only outside the cons for testing
    int tileHeightCount; // these are only outside the cons for testing

    bool headHitDot(); // returns true if the head collides with the dot
    void eatAndMoveDot(); // eats the dot and moves dot
    void addSnakePart(); // generates snake part

public:
    SnakeGame();
    bool checkHeadCollision(); // check for collision between head and the rest of the body

    void render(); //render all tiles on map
    void handleInput(SDL_Event &event);
    void moveSnake(); //move the snake around the screen
};

#endif