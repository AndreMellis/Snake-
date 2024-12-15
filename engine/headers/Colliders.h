#ifndef COLLIDERS_HEADER_
#define COLLIDERS_HEADER_

#include <SDL.h>
#include <vector>

class Colliders
{
public:
    // takes in a rectangle and a vector of rectangles, then checks for collision
    bool checkCollision(SDL_Rect *mainRect, std::vector<SDL_Rect*> *allColliders);

};

#endif