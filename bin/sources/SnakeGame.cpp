#include "SnakeGame.h"
#include <cstdio>
#include <string>


SnakeGame::SnakeGame()
{
    //int tileWidthCount = pWindowRenderer->getWindowWidth() / TILE_WIDTH; //TILEWIDTH defined in Tile.h
    //int tileHeightCount = pWindowRenderer->getWindowHeight() / TILE_HEIGHT; //TILEWIDTH defined in Tile.h
    tileWidthCount = pWindowRenderer->getWindowWidth() / TILE_WIDTH; //TILEWIDTH defined in Tile.h
    tileHeightCount = pWindowRenderer->getWindowHeight() / TILE_HEIGHT; //TILEWIDTH defined in Tile.h

    // setting the size out the gate so that we don't waste mem later
    mainMap.resize(tileHeightCount);
    for(auto &i : mainMap)
    {
        i.resize(tileWidthCount);
    }

    // fill map with thiles
    for( int y = 0; y < mainMap.size(); y++)
    { // for each row 
        for( int x = 0; x < mainMap[y].size(); x++ )
        {
            mainMap[y][x] = new Tile( x * TILE_WIDTH, y * TILE_WIDTH);
        }
    }

    mVelY = 0;
    mVelX = 0;

    // set the head
    mPosY = tileHeightCount/2;
    mPosX = tileWidthCount/2;
    mainMap[mPosY][mPosX]->toggleOccupied();

    snakeParts.insert(snakeParts.begin(), std::make_pair(mPosY,mPosX));

    dotY = rand() % (tileHeightCount-1);
    dotX = rand() % (tileWidthCount-1);
    mainMap[dotY][dotX]->toggleOccupied();
}

void SnakeGame::render()
{ // print all occupied tiles
    for( int y = 0; y < mainMap.size(); y++)
    { // for each row 
        for( int x = 0; x < mainMap[y].size(); x++ )
        {
            mainMap[y][x]->render();
        }
    }

    // print out score
    std::string pointStr = "SCORE: " + std::to_string(score.getScore());
    pWindowRenderer->drawString(pointStr, &scoreBoard);
}

void SnakeGame::handleInput(SDL_Event &event)
{
    if( event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_w:
            case SDLK_UP:
                // so if w or UP, then
				if( mVelY != 1 )
				{ //we don't want to reverse
                	mVelY = -1;
                	mVelX = 0;
				}
                break;
            
            case SDLK_s:
            case SDLK_DOWN:
                // so if s or DOWN, hen
				if( mVelY != -1)
				{
                	mVelY = 1;
                	mVelX = 0;
				}
                break;
            
            case SDLK_d:
            case SDLK_RIGHT:
				if(mVelX != -1)
				{
                	mVelY = 0;
                	mVelX = 1;
				}
                break;
            
            case SDLK_a:
            case SDLK_LEFT:
				if(mVelX != 1)
				{
                	mVelY = 0;
                	mVelX = -1;
				}
                break;
        }
    }
}

void SnakeGame::moveSnake()
{
    // move the head cords
    mPosY += mVelY;
    mPosX += mVelX;

    // for now I just won't let you go out of bounds
    if( mPosY < 0 || mPosY > (tileHeightCount-1) )
        mPosY -= mVelY;
    if ( mPosX < 0 || mPosX > (tileWidthCount-1) )
        mPosX -= mVelX;

    // add new head at begining
    snakeParts.insert( snakeParts.begin(), std::make_pair(mPosY, mPosX) );
    mainMap[snakeParts.front().first][snakeParts.front().second]->toggleOccupied();

    if (headHitDot())
    { // if we hit a dot eat and mvoe the dot, but keep the extra body piece
        score.increaseScore();
        eatAndMoveDot();
    } else
    { // remove the extra body piece
        mainMap[snakeParts.back().first][snakeParts.back().second]->toggleOccupied();
        snakeParts.pop_back();
    }
}

void SnakeGame::eatAndMoveDot()
{
    mainMap[dotY][dotX]->toggleOccupied();

    do
    {
        dotY = rand() % ( mainMap.size() - 1 );
        dotX = rand() % ( mainMap[0].size() - 1 );
    } while ( mainMap[dotY][dotX]->isOccupied() ); // if the snake is there, go somewhere else

    mainMap[dotY][dotX]->toggleOccupied();
}

bool SnakeGame::headHitDot()
{
    return mPosY == dotY && mPosX == dotX;
}

bool SnakeGame::checkHeadCollision()
{
    SDL_Rect *headBox = mainMap[ snakeParts.front().first ][ snakeParts.front().second ]->getCords();

    for(int i = 1; i < snakeParts.size(); i++)
    {
        if(SDL_HasIntersection ( 
            headBox,
            mainMap[ snakeParts.at(i).first ][ snakeParts.at(i).second ]->getCords()
         ))
         {
            return 1;
         }
    }

    return 0;
}
