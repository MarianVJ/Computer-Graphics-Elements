#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Platform
{
public:
	Platform();
	Platform(float tx, float ty);
	~Platform();
	//Coordonatele centrului 
	float x, y;
	//Coordonatele mouseului
	float mx, my;
	//Diferenta pentru x si y ( ale mosului) 
	float dx, dy;
	float oldx, oldy;
	//Dimensiunile platformei
	float width = 210;
	float height = 12;
	int sw = 0;
private:
protected:
};
