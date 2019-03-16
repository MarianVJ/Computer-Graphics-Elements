#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Ball
{
public:
	Ball();
	Ball(float tx, float ty, float tz, float radiusX);
	~Ball();
	//Coordonatele centrului  bilei
	float x, y,z;
	//1 pentru rosu , 2 pentru galben , 3 pentru negru
	int color;

	//Aceeasta raza este modificata atunci cand se ia un anumit powerup
	float radius = 12;

	//vitezele
	float vx = 0;
	float vz = 0;

	float ax = 100;
	float az = 60;

	float px;
	float py;
	float mass = 10;
	bool viata = true;

	float xcopie;
	float zcopie;

	float restartX;
	float restartZ;

	int id = 0;

	
	


	int start = 0;
	bool turned;

private:


protected:

};
