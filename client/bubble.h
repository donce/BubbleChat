#ifndef BUBBLE_H
#define BUBBLE_H

#include "point.h"
#include <string>

class Bubble {
	static const double SPEED = 5*64;
	Point pos;
	Point dir;
	std::string name;
public:
	Bubble();
	Point getPos() const;
	void setName(std::string name);
	void setDir(Point dir);
	void progress(int time);
	void say(std::string message);
};

#endif
