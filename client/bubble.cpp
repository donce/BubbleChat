#include "bubble.h"
#include <iostream>

Bubble::Bubble() {
}

Point Bubble::getPos() const {
	return pos;
}

void Bubble::setName(std::string name) {
	this->name = name;
}

void Bubble::setDir(Point dir) {
	this->dir = dir;
}

void Bubble::progress(int time) {
	pos.x += SPEED * time * dir.x / 1000;
	pos.y += SPEED * time * dir.y / 1000;
}

void Bubble::say(std::string message) {
	std::cout << name << ": " << message << std::endl;
}
