#include "world.h"
#include <string>
#include "display.h"

const int WORLD_IMAGES_COUNT = 2;
const char *WORLD_IMAGES[WORLD_IMAGES_COUNT] = {
	"ground",
	"ground2",
};

SDL_Surface* World::getSurface() {
	SDL_Surface *world_images[WORLD_IMAGES_COUNT];
	for (int i = 0; i < WORLD_IMAGES_COUNT; ++i) {
		std::string s = std::string("data/world/") + WORLD_IMAGES[i] + std::string(".bmp");
		world_images[i] = Display::loadBMP(s.c_str());
	}
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
			SDL_BlitSurface(world_images[(i+j)%2], &rSrc, world, &rDst);
		}
	return world;
}
