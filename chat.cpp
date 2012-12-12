#include "display.h"
#include "bubble.h"

#include <vector>

#define DIRS_COUNT 4
const int DIRS[DIRS_COUNT][2] = {
	{0, -1},
	{0, 1},
	{1, 0},
	{-1, 0}
};

Display display;

std::vector<Bubble> bubbles;

bool dirButtons[DIRS_COUNT];//up, down, right, left
bool dirChanged;

void progress(int time) {
	for (int i = 0; i < bubbles.size(); ++i)
		display.cleanBubble(bubbles[i]);
	for (int i = 0; i < bubbles.size(); ++i)
		bubbles[i].progress(time);
	for (int i = 0; i < bubbles.size(); ++i)
		display.drawBubble(bubbles[i]);
	display.progress();
}

int main() {
	display.init(true);
	//display.init(false, 640, 480);

	Bubble me;
	bubbles.push_back(me);

	Uint32 ticks = SDL_GetTicks();
	bool running = true;
	while (running) {
		SDL_Event e;
		dirChanged = false;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				running = 0;
			else if (e.type == SDL_KEYDOWN) {
				int nr = e.key.keysym.sym;
				if (nr == 27)
					running = false;
				else if (nr >= 273 && nr <= 276) {
					dirButtons[nr-273] = true;
					dirChanged = true;
				}
				else
					printf("Unused button down: %d\n", nr);
			}
			else if (e.type == SDL_KEYUP) {
				int nr = e.key.keysym.sym;
				if (nr >= 273 && nr <= 276) {
					dirButtons[nr-273] = false;
					dirChanged = true;
				}
			}
		}
		if (dirChanged) {
			Point newDir;
			for (int i = 0; i < DIRS_COUNT; ++i)
				if (dirButtons[i]) {
					newDir.x += DIRS[i][0];
					newDir.y += DIRS[i][1];
				}
			bubbles[0].setDir(newDir);
		}
		Uint32 nowTics = SDL_GetTicks();
		progress(nowTics - ticks);
		ticks = nowTics;
	}
	SDL_Quit();

	return 0;    
}
