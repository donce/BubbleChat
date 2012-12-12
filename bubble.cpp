#include "bubble.h"

Bubble::Bubble() {
}

Point Bubble::getPos() const {
	return pos;
}

void Bubble::setDir(Point dir) {
	this->dir = dir;
}

void Bubble::progress(int time) {
	pos.x += SPEED * time * dir.x / 1000;
	pos.y += SPEED * time * dir.y / 1000;
}
