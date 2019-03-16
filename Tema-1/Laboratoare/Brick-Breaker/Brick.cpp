#include "Brick.h"

#include <vector>
#include <iostream>



Brick::Brick()
{
}

Brick::~Brick()
{
}

Brick::Brick(float tx, float ty, float heightA, float widthA) {
	this->x = tx;
	this->y = ty;
	this->height = heightA;
	this->width = widthA;
	this->state = false;
	this->centerX = this->x + this->width / 2;
	this->centerY = this->y + this->height / 2;
}
