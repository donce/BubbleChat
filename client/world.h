#ifndef WORLD_H
#define WORLD_H

#include "SDL/SDL.h"

class World {
	int width, height;
	int *data;
	int tileCount;
	SDL_Surface **tiles;
public:
	World(const char *file);
	SDL_Surface* getSurface();//TODO: const
};

#endif
