#ifndef BUBBLE_H
#define BUBBLE_H

#include "point.h"
#include <string>

class Bubble {
	static const double SPEED = 5*64;
	Point pos;
	Point dir;
	int id;
	std::string name;
public:
	Bubble();
	Point getPos() const;
	void setPos(Point _pos);
	int getID();
	void setID(int id);
	void setName(std::string name);
	std::string getName();
	void setDir(Point dir);
	Point getDir();
	void progress(int time);
	void say(std::string message);
	Bubble *bubbleAt(int i);
};

#endif
