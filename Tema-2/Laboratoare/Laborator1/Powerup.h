#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Powerup
{
public:
	Powerup();
	Powerup(float tx, float ty,int type);
	~Powerup();
	//Coordonatele coltului stanga jos
	float x, y;
	//latimea = lungimea ( sunt patrate)
	float height = 20;
	//Unghiul cu care sunt rotite pt animatie 
	float angle = 12;

	//Centrul unei caramizi(dreptunghi) de dimensiuni height , width cu coltul in x , y
	float centerX;
	float centerY;

	//Tipul de powerup
	int type;
private:
protected:
};
