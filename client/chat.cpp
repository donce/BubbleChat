#include "chat.h"

#include <iostream>

Bubble* Chat::me() {
	if (myIndex < 0 || myIndex >= bubbles.size())
		throw "My bubble index out of range!";
	return &bubbles[myIndex];
}

Chat::Chat(std::string name, bool fullscreen, int width, int height) {
	myIndex = 0;
	Bubble myBubble;
	bubbles.push_back(myBubble);
	me()->setName(name);
	display.init(fullscreen, width, height);
}

void Chat::progress(int time) {
	for (int i = 0; i < bubbles.size(); ++i)
		display.cleanBubble(bubbles[i]);
	for (int i = 0; i < bubbles.size(); ++i)
		bubbles[i].progress(time);
	for (int i = 0; i < bubbles.size(); ++i)
		display.drawBubble(bubbles[i]);
	display.progress();
}

void Chat::sayMessage(std::string s) {
	me()->say(s);
}

void Chat::setDir(Point dir) {
	bubbles[myIndex].setDir(dir);
}
