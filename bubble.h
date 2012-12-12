#ifndef BUBBLE_H
#define BUBBLE_H

#include "point.h"

class Bubble {
	static const double SPEED = 5;
	Point pos;
	Point dir;
public:
	Bubble();
	Point getPos() const;
	void setDir(Point dir);
	void progress(int time);
};

#endif
