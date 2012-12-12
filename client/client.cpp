#include <iostream>

#include "chat.h"

using namespace std;

#define DIRS_COUNT 4
const int DIRS[DIRS_COUNT][2] = {
	{0, -1},
	{0, 1},
	{1, 0},
	{-1, 0}
};
bool dirButtons[DIRS_COUNT];//up, down, right, left
bool dirChanged;

int main() {
	string name;
	cout << "Enter your name: ";
	cin >> name;

	Chat chat(name, false, 640, 480);
	Uint32 ticks = SDL_GetTicks();
	string message = "";

	bool running = true;
	while (running) {
		SDL_Event e;
		dirChanged = false;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				running = 0;
			else if (e.type == SDL_KEYDOWN) {
				int nr = e.key.keysym.sym;
				if (nr == SDLK_ESCAPE)
					running = false;
				else if (nr >= 273 && nr <= 276) {
					if (!dirButtons[nr-273])
						dirChanged = true;
					dirButtons[nr-273] = true;
				}
				else if (nr == SDLK_RETURN) {
					chat.sayMessage(message);
					message = "";
				}
				else if (nr == SDLK_BACKSPACE){
					if (message.length())
						message.erase(message.length()-1, 1);
				}
				else
					message += e.key.keysym.sym;
			}
			else if (e.type == SDL_KEYUP) {
				int nr = e.key.keysym.sym;
				if (nr >= 273 && nr <= 276) {
					if (dirButtons[nr-273])
						dirChanged = true;
					dirButtons[nr-273] = false;
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
			chat.setDir(newDir);
		}
		Uint32 nowTics = SDL_GetTicks();
		chat.progress(nowTics - ticks);
		ticks = nowTics;
	}
	SDL_Quit();

	return 0;    
}
