#ifndef WORLD_H
#define WORLD_H

#include "SDL/SDL.h"

class World {
	int width, height;
	int *data;
public:
	SDL_Surface* getSurface();//TODO: const
};

#endif
