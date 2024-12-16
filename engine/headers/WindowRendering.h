#ifndef WINDOWRENDERING_HEADER
#define WINDOWRENDERING_HEADER

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class WindowRendering
{
private:
	// singleton crud
	WindowRendering();
	~WindowRendering();
	static WindowRendering *pInstance;

	//vars
	SDL_Window *gWindow; //main game window
	SDL_Renderer *gRenderer;
	SDL_Texture *gTextureBuffer;
	int windowHeight;
	int windowWidth;

	SDL_Texture *stringToSurface(std::string inputStr, SDL_Color color, int fontSize, std::string fontName);

public:
	static WindowRendering *getInstance();

	void clearBuffer(); // clears buffer to black
	void renderPresent() { SDL_RenderPresent( gRenderer ); } // draw buffer to screen
	void close();

	int getWindowHeight() { return windowHeight; }
	int getWindowWidth() { return windowWidth; }


	void drawSolidRect(SDL_Rect *shape);
	void drawString(std::string inputStr, SDL_Rect *shape); // draws a string to screen
};

#endif
