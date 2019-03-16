#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include "Brick.h"
#include "Ball.h"
#include "Platform.h"
#include "Game.h"
#include "Powerup.h"
#include <ctime>


class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;
	void printBricks(float deltaTimeSeconds);
	void initBricks(float firstX, float firstY);

	//Scopul fiecarei din aceste metode este descrisa inainte de definirea lor

	void drawPowerups(float deltaTimeSeconds);
	void drawWalls();
	void initWalls();
	void checkBrickCollision();
	void checkWallCollision();

	void checkPlatformPowerupCollision();
	void checkPlatformCollision();
	//Aceasta functie indeplineste acelasi lucru( dar este implementata altfel)
	void checkPlatformCollision2();
	void calculateDistance(Brick *b);
	void checkGameConditions();
	void drawBallandLifes();
	void collision();


protected:
	glm::mat3 modelMatrix;
	//Vector care contine toate obiectele de tip caramida specifice scenei
	std::vector<Brick*> bricks;
	//Vector in care se adauga , atunci cand sunt generate powerups urile
	std::vector<Powerup*> powerups;

	//Primii 3 , sunt obiecte pentru pereti , iar ultimul este peretele
	//generate la prinderea unui powerup
	Brick* wall1;
	Brick* wall2;
	Brick* wall3;
	Brick* wall4;
	//Obiectul care incapsuleaza informatiile specifice bilei
	Ball *ball;
	//Obiect care incapsuleaza informatiile specifice platformei
	Platform* platform;
	//Detaliile despre joc ( per ansamblu) sunt incapsulate cu ajutorul
	//acestui obiect de tip Game
	Game* game;
	//Un powerup auxiliar utilizat in interiorul programului
	Powerup* aux_powerup = new Powerup(100, 600,1);
};
