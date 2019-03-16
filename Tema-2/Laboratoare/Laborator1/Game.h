#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include <ctime>

class Game
{
public:
	Game();
	Game(float widthX, float heightY);
	~Game();
	//dimensiunile ferestrei
	float  width, height;
	//numarul de linii si de coloane ( de caramizi )
	int lines;
	int columns;
	//Numarul de vieti al jucatorului
	int lifes = 3;
	//Aceste variabile boolene indica daca unul din cele 3 powerupuri a fost activat
	bool type1 = false;
	bool type2 = false;
	bool type3 = false;
	//Aceste variabile de tip clock retin ora la care a foct activat utlima
	//data un powerup 1 2 sau 3 . Apoi la 30 se secunde acesta este oprit
	std::clock_t start1;
	std::clock_t start2;
	std::clock_t start3;
	//Variabile care retine ultimul bonus/powerup ce a fost "prins"
	//Si ajuta la colorarea platformei si a peretilor in culoarea specifica
	int lastbonus = 0;
	//Aceasta variabila retine cate bile au fost distruse pana acum 
	//Iar atunci cand ea este egala cu lines*columns( in cazul de fata 120)
	//Jocul se reia de la capat
	int destroyedBalls = 0;
private:
protected:
};
