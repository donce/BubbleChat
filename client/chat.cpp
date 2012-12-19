#include "chat.h"

#include <iostream>

Bubble* Chat::me() {
	if (myIndex < 0 || myIndex >= bubbles.size())
		throw "My bubble index out of range!";
	return &bubbles[myIndex];
}

Chat::~Chat()
{
}

Chat::Chat(std::string name, Network *_net, bool fullscreen, int width, int height) {
	myIndex = 0;
	Bubble *myBubble = new Bubble();
	bubbles.push_back(*myBubble);
	me()->setName(name);
	display.init(fullscreen, width, height);
	net = _net;
	if(!net->initConnection(me()))
		exit(0);
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
	net->sendMessage((uint8_t *)s.c_str());
}

void Chat::setDir(int idx, Point dir)
{
	//if index is not known, just use me :D:w
	if(idx < 0 || idx >= bubbles.size())
		idx = myIndex;

	bubbles[idx].setDir(dir);

	//if we are setting to ourselves
	//send it to server
	if(&bubbles[idx] == me()){
		movementCommand_t move;
		Point pos = bubbles[idx].getPos();
		Point dir = bubbles[idx].getDir();
	
		move.x = pos.x;
		move.y = pos.y;
		move.dirX = dir.x;
		move.dirY = dir.y;

		net->sendPos(move);
	}
}

void Chat::addBubble(Bubble b)
{
	bubbles.push_back(b);

	return;
}

void Chat::remBubble(int id)
{
	//find our bubble
	int i;
	for(i = 0; i < bubbles.size(); i++)
		if(bubbles[i].getID() == id)
			break;

	if(i >= bubbles.size())
		return;

	//erase it
	
	bubbles.erase(bubbles.begin() + i);
	
	return;
}

Bubble *Chat::bubbleAt(int i)
{
	if(i < 0 || i >= bubbles.size())
		return NULL;

	return &bubbles[i];
}

int Chat::bubbleCnt()
{
	return bubbles.size();
}
