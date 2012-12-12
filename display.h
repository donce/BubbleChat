#ifndef DISPLAY_H
#define DISPLAY_H

#include "SDL/SDL.h"
#include "point.h"
#include "bubble.h"

class Display {
	SDL_Surface *screenSurface;
	SDL_Surface *bubbleSurface;
	SDL_Surface *worldSurface;
public:
	void init(bool fullscreen, int width = -1, int height = -1);
	void draw(SDL_Surface *image, Sint16 x, Sint16 y);
	void draw(SDL_Surface *image, Point p);

	void clean(SDL_Rect &rect);
	void cleanBubble(const Bubble &bubble);
	void drawBubble(const Bubble &buble);

	void progress();
};

#endif
