#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
//Desi aceasta clasa se numeste "Brick", ea a fost utilizata
//pentru a incapsula informatia si epntru pereti ( deoarece au aceeasi forma)



class Paralelipiped
{
public:
	Paralelipiped();
	Paralelipiped( float widthA, float heightA, float lengthA);

	~Paralelipiped();


	//Coordonatele coltului stanga jos
	float x, y,z;
	float zz;

	//inaltime si latimea unui Brick
	float height, width, length;

	//Centrul unei caramizi(dreptunghi) de dimensiuni height , width cu coltul in x , y
	float centerX;
	float centerZ;




private:


protected:

	//Daca este distrusa sau nu
	bool state;

};
