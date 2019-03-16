#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include "LabCamera.h"
#include "Ball.h"
#include "Paralelipiped.h"
#include "Game.h"


class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();

	void Init() override;

	Mesh * CreateMesh(const char * name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices);

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;


	///AICI MODIFIC CAMERA
	void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix);
	void RenderMeshColor(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, glm::vec3 color);

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

	//Verifica coliziune dintre bile si pereti
	void checkWallCollision();
	void checkWallCollision2();

	void calculateDistance(Paralelipiped *p, Ball *b);
	void calculateDistance2(Paralelipiped *p, Ball *b);

	void checkBuzunareCollision();
	void checkBalltoBallCollision();

protected:
	Laborator::MyCamera *camera;
	glm::mat4 projectionMatrix;
	bool renderCameraTarget;
	std::vector<Ball*> buzunare;
	std::vector<Ball*> bile;
	Ball* alba;
	Paralelipiped* wall1, *wall2, *wall3, *wall4;
	Paralelipiped* masa;
	Game* game;
	Paralelipiped *tac;
	float unghi = 0;
	float auxConstr[4][4] = { {1, -0.000378232, 3.70479, 0}, {0, 0.00979455, 0.999952, 0}, {-0.00037825,  -0.999952, 0.00979455, 0}, {-0 ,-0 ,-3.35378 ,1}};
	glm::mat4 matriceVizualizare;
	glm::mat4 matriceProiectie;
	float power;


};
