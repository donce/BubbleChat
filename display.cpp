#include "display.h"

void Display::init(bool fullscreen, int width, int height) {
//void Display::init(int width, int height, bool fullscreen) {
	SDL_Init(SDL_INIT_VIDEO);
	Uint32 flags = SDL_SWSURFACE;
	if (fullscreen)
		flags |= SDL_FULLSCREEN;
	if (width == -1 || height == -1) {
		const SDL_VideoInfo *info = SDL_GetVideoInfo();
		width = info->current_w;
		height = info->current_h;
	}
	screenSurface = SDL_SetVideoMode(width, height, 32, flags);

	bubbleSurface = SDL_LoadBMP("data/bubble.bmp");
}

void Display::draw(SDL_Surface *image, Sint16 x, Sint16 y) {
	SDL_Rect rSrc, rDst;
	rSrc.w = rDst.w = image->w;
	rSrc.h = rDst.h = image->h;
	rSrc.x = rSrc.y = 0;
	rDst.x = x;
	rDst.y = y;
	SDL_BlitSurface(image, &rSrc, screenSurface, &rDst);
	SDL_UpdateRects(screenSurface, 1, &rDst);
}

void Display::draw(SDL_Surface *image, Point p) {
	draw(image, p.x, p.y);
}

void Display::cleanBubble(const Bubble &bubble) {
	
}

void Display::drawBubble(const Bubble &bubble) {
	draw(bubbleSurface, bubble.getPos());
}
