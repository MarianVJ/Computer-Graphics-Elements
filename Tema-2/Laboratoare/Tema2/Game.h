#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include <ctime>

class Game
{
public:
	Game();
	~Game();

	bool start = false;
	float limitSupX, limitSupZ;
	float limitInfX, limitInfZ;
	bool lookAtBall = false;
	bool startPower = false;
	float angle = 0;
	clock_t time;



	//0 bila trebuie asezata de catre jucator pe masa (din cauuza ca este inceput de meci sau fault)
	//2 bila se afla in miscare in urma unei lovituri
	//1 jucatorul roteste takul in jurul bilei 
	int pozitionareBila = 0;
	bool startTinta = false;

	int oldRunda = -1;
	int runda = 0;
	int punctePlayer1 = 0;
	int punctePlayer2 = 0;

	int faultPlayer1=  0;
	int faultPLayer2 = 0;
	int jucatorActual = -1;
	

	//Tipul de vedere ( TOP DOWN = 1 , THIRD_PERSON  = 2) (initial trebuie pozitionata bila pe masa)
	int tipVedere = 1;


	


private:


protected:


};
