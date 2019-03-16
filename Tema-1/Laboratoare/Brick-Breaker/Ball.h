#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Ball
{
public:
	Ball();
	Ball(float tx, float ty);
	~Ball();
	//Coordonatele centrului  bilei
	float x, y;
	//Initial bila va fi deplasata doar pe OY 
	float speedX = 0;
	float speedY = 270;
	//Valoarea razei initiala
	float initialRadius = 12;
	//Aceeasta raza este modificata atunci cand se ia un anumit powerup
	float radius = 12;
	int start = 0;
	bool turned;

private:


protected:

};
