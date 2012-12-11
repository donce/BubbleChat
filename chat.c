#include "SDL/SDL.h"

SDL_Surface *screen;

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(1366, 768, 32, SDL_SWSURFACE);

	int running = 1;
	while (running) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				running = 0;
		}
	}
	SDL_Quit();

	return 0;    
}
