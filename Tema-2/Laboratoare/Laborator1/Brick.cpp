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
[1 -0.000732614 4.32171e-05 0]
0.000194 4.484261 0.264528
--------
[-3.86113e-12 0.0588879 0.998265 0]
0.000194 4.484261 0.264528
--------
[-0.000733888 -0.998264 0.0588879 0]
0.000194 4.484261 0.264528
--------
[1.45519e-11 5.96046e-08 -4.49206 1]
-----------
[0.125, 0 ,0 ,0]
[0, 0.222222 ,0, 0]
[0, 0 ,-0.10005, 0]
[-0 ,-0, -1.001, 1]

[0.00205182 4.48898 0.289898]



[-0.408714 ,5.09563 ,0.154581]
[-0.00420936 ,0.0464794 ,-0.99891]












