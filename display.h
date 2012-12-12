#ifndef DISPLAY_H
#define DISPLAY_H

#include "SDL/SDL.h"
#include "point.h"
#include "bubble.h"

const int TRANSPARENT_COLOR = 0xFF00FF;

class Display {
	SDL_Surface *screenSurface;
	SDL_Surface *bubbleSurface;
	SDL_Surface *worldSurface;
public:
	void init(bool fullscreen, int width, int height);
	void draw(SDL_Surface *image, Sint16 x, Sint16 y);
	void draw(SDL_Surface *image, Point p);

	void clean(SDL_Rect &rect);
	void cleanBubble(const Bubble &bubble);
	void drawBubble(const Bubble &buble);

	void progress();

	static SDL_Surface* loadBMP(const char *file);
};

#endif
