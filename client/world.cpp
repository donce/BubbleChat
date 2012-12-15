#include "world.h"
#include "display.h"
#include <string>
#include <fstream>

using namespace std;

const int BLOCK_SIZE = 64;

World::World(const char *file) {
	ifstream f(file);
	f >> tileCount;
	tiles = new SDL_Surface*[tileCount];
	for (int i = 0; i < tileCount; ++i) {
		string title;
		f >> title;
		string filename = string("data/world/") + title + string(".bmp");
		tiles[i] = Display::loadBMP(filename.c_str());
		if (tiles[i]->w != BLOCK_SIZE || tiles[i]->h != BLOCK_SIZE)
			throw "Wrong tile texture size";
	}
	f >> height >> width;
	data = new int[width*height];
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j) {
			int now;
			if (!(f >> now))
				throw "Failed to read tile number";
			if (now < 0 || now >= tileCount)
				throw "Map tile number out of bounds";
			data[i*width+j] = now;
		}
	f.close();
}

SDL_Surface* World::getSurface() {
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
			SDL_BlitSurface(tiles[data[i*height+j]], &rSrc, world, &rDst);
		}
	return world;
}
