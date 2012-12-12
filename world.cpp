#include "world.h"


SDL_Surface* World::getSurface() {
	SDL_Surface *groundSurface;
	groundSurface = SDL_LoadBMP("data/ground.bmp");

	const int BLOCK_SIZE = 64;

	//TODO:REMOVE
	width = 10;
	height = 10;

	Uint32 flags;
	SDL_Surface *world = SDL_CreateRGBSurface(flags, width*BLOCK_SIZE, height*BLOCK_SIZE, 32, 0, 0, 0, 0);

	SDL_Rect rSrc;
	rSrc.x = rSrc.y = 0;
	rSrc.w = rSrc.h = BLOCK_SIZE;
	SDL_Rect rDst;
	rDst.w = rDst.h = BLOCK_SIZE;

	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; j++) {
			rDst.x = j*BLOCK_SIZE;
			rDst.y = i*BLOCK_SIZE;
			SDL_BlitSurface(groundSurface, &rSrc, world, &rDst);
		}
	return world;
}
