#ifndef CHAT_H
#define CHAT_H

#include "network.h"
#include "bubble.h"
#include "display.h"

#include <string>
#include <vector>


class Chat {
	std::vector<Bubble> bubbles;
	
	int myIndex;
	Bubble* me();

	Network *net;

	Display display;
public:
	Chat(std::string name, Network *net, bool fullscreen = true, int width = -1, int height = -1);
	~Chat();
	void progress(int time);
	void setDir(int idx, Point dir);
	void sayMessage(std::string s);
	void addBubble(Bubble b);
	void remBubble(int id);
	Bubble *bubbleAt(int i);
	int bubbleCnt();
};
	

extern Chat *chatObject;
#endif
