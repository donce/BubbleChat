#ifndef CHAT_H
#define CHAT_H

#include "bubble.h"
#include "display.h"

#include <string>
#include <vector>


class Chat {
	std::vector<Bubble> bubbles;
	
	int myIndex;
	Bubble* me();

	Display display;
public:
	Chat(std::string name, bool fullscreen = true, int width = -1, int height = -1);
	void progress(int time);
	void setDir(Point dir);
	void sayMessage(std::string s);
};
	
#endif
