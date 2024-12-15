#include "Colliders.h"

bool Colliders::checkCollision(SDL_Rect *mainRect, std::vector<SDL_Rect*> *allColliders)
{
    for(int i = 0; i < allColliders->size(); i++)
    {
        if ( SDL_HasIntersection( mainRect, allColliders->at(i) ) ) // cannot use allColliders[i] because it's a pointer to vec
        { // if mainRect intersects with any collider, we have a collision
            return 1;
        }
    }
    return 0; // no collision
}