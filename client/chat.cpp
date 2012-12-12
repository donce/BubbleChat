#include "chat.h"

Chat::Chat(bool fullscreen, int width, int height) {
	display.init(fullscreen, width, height);
	myIndex = 0;
	Bubble me;
	bubbles.push_back(me);
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
	printf("Message: %s\n", s.c_str());
}
void Chat::setDir(Point dir) {
	bubbles[myIndex].setDir(dir);
}
