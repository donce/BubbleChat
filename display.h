#ifndef DISPLAY_H
#define DISPLAY_H

#include "SDL/SDL.h"
#include "point.h"
#include "bubble.h"

class Display {
	SDL_Surface *screenSurface, *bubbleSurface;
public:
	void init(bool fullscreen, int width = -1, int height = -1);
	void draw(SDL_Surface *image, Sint16 x, Sint16 y);
	void draw(SDL_Surface *image, Point p);

	void cleanBubble(const Bubble &bubble);
	void drawBubble(const Bubble &buble);
};

#endif
