#include <stdbool.h>
#include "SDL/SDL.h"

#define DIRS_COUNT 4
const int DIRS[DIRS_COUNT][2] = {
	{0, -1},
	{0, 1},
	{1, 0},
	{-1, 0}
};

SDL_Surface *screen;
int acceleration[2];
int bx, by;

bool dirButtons[DIRS_COUNT];//up, down, right, left

void draw(SDL_Surface *image, Sint16 x, Sint16 y) {
	SDL_Rect rSrc, rDst;
	rSrc.w = rDst.w = image->w;
	rSrc.h = rDst.h = image->h;
	rSrc.x = rSrc.y = 0;
	rDst.x = x;
	rDst.y = y;
	SDL_BlitSurface(image, &rSrc, screen, &rDst);
	SDL_UpdateRects(screen, 1, &rDst);
}

int main(int argc, char* args[]) {
	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(1366, 768, 32, SDL_SWSURFACE | SDL_FULLSCREEN);

	SDL_Surface *bubble = SDL_LoadBMP("data/bubble.bmp");
	bool running = true;
	while (running) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				running = 0;
			else if (e.type == SDL_KEYDOWN) {
				int nr = e.key.keysym.sym;
				if (nr == 27)
					running = false;
				else if (nr >= 273 && nr <= 276)
					dirButtons[nr-273] = true;
				else
					printf("Unused button down: %d\n", nr);
			}
			else if (e.type == SDL_KEYUP) {
				int nr = e.key.keysym.sym;
				if (nr >= 273 && nr <= 276)
					dirButtons[nr-273] = false;
			}
		}
		acceleration[0] = acceleration[1] = 0;
		for (int i = 0; i < DIRS_COUNT; ++i)
			if (dirButtons[i]) {
				acceleration[0] = DIRS[i][0];
				acceleration[1] = DIRS[i][1];
			}
		bx += acceleration[0];
		by += acceleration[1];
		draw(bubble, bx, by);
		SDL_Delay(1);
	}
	SDL_Quit();

	return 0;    
}
