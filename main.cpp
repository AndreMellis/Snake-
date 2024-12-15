#include "WindowRendering.h"
#include "SnakeGame.h"
#include "LTimer.h"

#include <cstdlib>
#include <ctime>
#include <SDL.h>

int main(int argc, char *args[])
{
    WindowRendering *pWindowRenderer = WindowRendering::getInstance();
    SnakeGame snakeGame;

    SDL_Event event;
    bool quit = 0;

    srand(time(0));

    // Window capping
    const int SCREEN_TICKS_PER_FRAME = 1000 / 30; // here 30 would be the max FPS
    LTimer capTimer;

    pWindowRenderer->clearBuffer(); //clearing buffer should always be first
    snakeGame.render();
    pWindowRenderer->renderPresent();

    do
    {
        capTimer.start(); // start counting how many frame ticks have passed
        while( SDL_PollEvent( &event ) != 0)          
        {
            if (event.type == SDL_QUIT)
            {
                quit = 1;
                pWindowRenderer->close();
                break;
            } else
            {
                snakeGame.handleInput(event);
            }
        }
        if(quit){break;}

        snakeGame.moveSnake();
        
        pWindowRenderer->clearBuffer();
        snakeGame.render();
        pWindowRenderer->renderPresent();

        if( capTimer.getTicks() < SCREEN_TICKS_PER_FRAME )
        { // we rendered too fast and need to wait
            SDL_Delay( SCREEN_TICKS_PER_FRAME - capTimer.getTicks() );
        }
    } while(quit != 1);

    return 1;
}
