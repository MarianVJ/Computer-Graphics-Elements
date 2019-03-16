#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
//Desi aceasta clasa se numeste "Brick", ea a fost utilizata
//pentru a incapsula informatia si epntru pereti ( deoarece au aceeasi forma)



class Brick 
{
public:
	Brick();
	Brick(float tx, float ty,float heightA, float widthA);
	~Brick();
	//Coordonatele coltului stanga jos
	float x, y;
	//inaltime si latimea unui Brick
	float height, width;
	//Speficia daca o anumita caramida este distrusa
	bool destroyed = false;
	//Centrul unei caramizi(dreptunghi) de dimensiuni height , width cu coltul in x , y
	float centerX;
	float centerY;
	//Factor de scalare folosit in cazul in care se distruge caramida
	float scale = 1;
	//Numarul de "vieti" ale unei caramizi ( de cate ori trebuie lovita pt a fi distrusa)
	int bricklifes = 4;

private:
	

protected:

	//Daca este distrusa sau nu
	bool state;
	
};
