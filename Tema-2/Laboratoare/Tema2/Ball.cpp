#include "Ball.h"

#include <vector>
#include <iostream>



Ball::Ball()
{
}

Ball::~Ball()
{
}


//Completez cu coordonatele centrului 
Ball::Ball(float x, float y,float z, float radiusX) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->radius = radiusX;

	this->restartX = x;
	this->restartZ = z;

	this->px = px;
	this->py = (-1) * z;

}
