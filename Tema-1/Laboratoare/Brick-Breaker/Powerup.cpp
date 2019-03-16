#include "Powerup.h"

#include <vector>
#include <iostream>



Powerup::Powerup()
{
}

Powerup::~Powerup()
{
}

Powerup::Powerup(float tx, float ty, int type) {

	this->x = tx;
	this->y = ty;
	this->type = type;

	this->centerX = this->x + this->height / 2;
	this->centerY = this->y + this->height / 2;

}
