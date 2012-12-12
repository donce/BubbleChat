#ifndef CHAT_H
#define CHAT_H

#include "bubble.h"
#include "display.h"

#include <string>
#include <vector>


class Chat {
	std::vector<Bubble> bubbles;
	int myIndex;

	Display display;
public:
	Chat(bool fullscreen = true, int width = -1, int height = -1);
	void progress(int time);
	void sayMessage(std::string s);
	void setDir(Point dir);
};
	
#endif
