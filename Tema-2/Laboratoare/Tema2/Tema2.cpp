#include "Tema2.h"
#include "Object3D.h"

#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <cmath>

#include <Core/Engine.h>

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	renderCameraTarget = false;

	camera = new Laborator::MyCamera();

	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));


	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}



	{
		masa = new Paralelipiped(2.3f, 0.3f, 3.1f);
		masa->x = -(masa->width / 2);
		masa->y = 1.5f;
		masa->z = masa->length / 2;

		wall1 = new Paralelipiped(0.1f, 0.2f, 3.1f);
		wall2 = new Paralelipiped(0.1f, 0.2f, 3.1f);
		wall3 = new Paralelipiped(2.3f, 0.2f, 0.1f);
		wall4 = new Paralelipiped(2.3f, 0.2f, 0.1f);


		wall1->y = wall2->y = wall3->y = wall4->y = masa->y + masa->height;

		wall1->x = -(masa->width / 2);
		wall2->x = -(masa->width / 2) + masa->width - wall2->width;
		wall2->z = wall1->z = masa->length / 2;

		wall3->x = wall4->x = -(masa->width / 2);
		wall4->z = masa->length / 2;
		wall3->z = -(masa->length / 2) + wall3->length;

		wall1->zz = (-1) * wall1->z;
		wall2->zz = (-1) * wall2->z;
		wall3->zz = (-1) * wall3->z;
		wall4->zz = (-1) * wall4->z;

		//Calculam centrele 
		wall1->centerX = wall1->x + wall1->width / 2;
		wall1->centerZ = wall1->zz + wall1->length / 2;

		wall2->centerX = wall2->x + wall2->width / 2;
		wall2->centerZ = wall2->zz + wall2->length / 2;

		wall3->centerX = wall3->x + wall3->width / 2;
		wall3->centerZ = wall3->zz + wall3->length / 2;

		wall4->centerX = wall4->x + wall4->width / 2;
		wall4->centerZ = wall4->zz + wall4->length / 2;




	}

	//Construim buzunarele pt masa
	{
		buzunare.push_back(new Ball(-masa->width / 2 + wall1->width, masa->y + masa->height, 0, 0.2f));
		buzunare.push_back(new Ball(masa->width / 2 - wall1->width, masa->y + masa->height, 0, 0.2f));

		float constanta = 0.025;
		buzunare.push_back(new Ball(masa->x + wall1->width + constanta, masa->y + masa->height, masa->z - wall3->length - constanta, 0.2f));

		buzunare.push_back(new Ball(masa->width / 2 - wall2->width - constanta, masa->y + masa->height, masa->z - wall3->length - constanta, 0.2f));

		buzunare.push_back(new Ball(masa->x + wall1->width + constanta, masa->y + masa->height, -masa->z + wall3->length + constanta, 0.2f));

		buzunare.push_back(new Ball(masa->width / 2 - wall2->width - constanta, masa->y + masa->height, -masa->z + wall3->length + constanta, 0.2f));

		alba = new Ball(masa->x / 6, masa->y + 0.15f / 2 + masa->height, masa->z / 1.5, 0.12f);


		//VITEZA
		alba->vx = -0.9f;
		alba->vz = -0.3f;

		tac = new Paralelipiped(0.02f, 0.06f, 2);
		tac->x = alba->x;
		tac->y = alba->y;
		tac->z = alba->z;
	}
	{




		//Stabilim valorile specifice pt ca jocul sa decurga conform cerintelor
		game = new Game();
		game->limitSupZ = masa->z - masa->length / 3 - alba->radius / 2;
		game->limitInfZ = masa->z - wall3->length - 0.04 - alba->radius / 2;


		game->limitSupX = masa->x + masa->width - wall1->width - alba->radius / 2 - 0.01;
		game->limitInfX = masa->x + wall1->width + alba->radius / 2 + 0.01;


	}
	{
		float pe_masa = masa->y + masa->height + alba->radius / 2;
		float raza = alba->radius;
		//Primul rand
		int i = 0;
		bile.push_back(new Ball(-(masa->width - 2 * wall1->width - 5 * raza) / 4 + 0.14, pe_masa, -masa->z + 0.25f, raza));
		bile[i++]->color = 1;
		bile.push_back(new Ball(bile[0]->x + raza, pe_masa, bile[0]->z, raza));
		bile[i++]->color = 1;
		bile.push_back(new Ball(bile[1]->x + raza, pe_masa, bile[0]->z, raza));
		bile[i++]->color = 2;
		bile.push_back(new Ball(bile[2]->x + raza, pe_masa, bile[0]->z, raza));
		bile[i++]->color = 2;
		bile.push_back(new Ball(bile[3]->x + raza, pe_masa, bile[0]->z, raza));
		bile[i++]->color = 1;
		//Al doilea rand 
		bile.push_back(new Ball(bile[0]->x + raza / 2, pe_masa, bile[0]->z + raza, raza));
		bile[i++]->color = 2;
		bile.push_back(new Ball(bile[5]->x + raza, pe_masa, bile[5]->z, raza));
		bile[i++]->color = 2;
		bile.push_back(new Ball(bile[6]->x + raza, pe_masa, bile[6]->z, raza));
		bile[i++]->color = 1;
		bile.push_back(new Ball(bile[7]->x + raza, pe_masa, bile[7]->z, raza));
		bile[i++]->color = 2;
		//Al trailea rand 
		bile.push_back(new Ball(bile[5]->x + raza / 2, pe_masa, bile[5]->z + raza, raza));
		bile[i++]->color = 2;
		bile.push_back(new Ball(bile[9]->x + raza, pe_masa, bile[9]->z, raza));
		bile[i++]->color = 3;
		bile.push_back(new Ball(bile[10]->x + raza, pe_masa, bile[10]->z, raza));
		bile[i++]->color = 1;
		//Al patrulea rand 
		bile.push_back(new Ball(bile[9]->x + raza / 2, pe_masa, bile[9]->z + raza, raza));
		bile[i++]->color = 1;
		bile.push_back(new Ball(bile[12]->x + raza, pe_masa, bile[12]->z, raza));
		bile[i++]->color = 2;
		//Ultima bila
		bile.push_back(new Ball(bile[12]->x + raza / 2, pe_masa, bile[12]->z + raza, raza));
		bile[i++]->color = 1;

	}


	// Create a simple cube
	{


		{
			//Definire masa 
			glm::vec3 corner = glm::vec3(0, 0, 0);
			// OX    INALTIME  OZ
			Mesh* picior = Object3D::CreateParalelipiped("picior", corner, 0.1f, 1.5f, 0.1f, glm::vec3(0.7f, 0.4f, 0));
			AddMeshToList(picior);

			Mesh* masa = Object3D::CreateParalelipiped("masa", corner, 2.3f, 0.3f, 3.1f, glm::vec3(0, 0.7f, 0));
			AddMeshToList(masa);

			Mesh* perete1 = Object3D::CreateParalelipiped("perete1", corner, 0.1f, 0.2f, 3.1f, glm::vec3(0, 0.3f, 0));
			AddMeshToList(perete1);

			Mesh* perete2 = Object3D::CreateParalelipiped("perete2", corner, 2.3f, 0.2f, 0.1f, glm::vec3(0, 0.3f, 0));
			AddMeshToList(perete2);



			Mesh* tac = Object3D::CreateTac("tac", corner, 0.02f, 0.06f, 2, glm::vec3(0.6, 0.25f, 0));
			AddMeshToList(tac);

			{
				Mesh* mesh = new Mesh("buzunar");
				mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
				meshes[mesh->GetMeshID()] = mesh;
			}

			{
				Mesh* mesh = new Mesh("alba");
				mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
				std::vector<VertexFormat>  nrm = mesh->vertices;
				glm::vec3 color = glm::vec3(1, 1, 1);
				for (int i = 0; i < mesh->positions.size(); i++) {
					nrm.push_back(VertexFormat(mesh->positions[i], color));
				}
				mesh->InitFromData(nrm, mesh->indices);
				AddMeshToList(mesh);
			}
			{
				Mesh* mesh = new Mesh("rosie");
				mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
				std::vector<VertexFormat>  nrm = mesh->vertices;
				glm::vec3 color = glm::vec3(1, 0, 0);
				for (int i = 0; i < mesh->positions.size(); i++) {
					nrm.push_back(VertexFormat(mesh->positions[i], color));
				}
				mesh->InitFromData(nrm, mesh->indices);
				AddMeshToList(mesh);
			}

			{
				Mesh* mesh = new Mesh("galbena");
				mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
				std::vector<VertexFormat>  nrm = mesh->vertices;
				glm::vec3 color = glm::vec3(1, 1, 0);
				for (int i = 0; i < mesh->positions.size(); i++) {
					nrm.push_back(VertexFormat(mesh->positions[i], color));
				}
				mesh->InitFromData(nrm, mesh->indices);
				AddMeshToList(mesh);
			}
		}



	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("ShaderTema2");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Am creat un nou shader separat pentru animatia tacului 
	{
		Shader *shader = new Shader("ShaderTema2Animatie");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader2.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader2.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
}

Mesh* Tema2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];
}


void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}



int oVariab = 0;
void Tema2::Update(float deltaTimeSeconds)
{


	//Desenare picioare masa
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.15f, 0, 1.55f));
		RenderSimpleMesh(meshes["picior"], shaders["ShaderTema2"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.15f + 2.3f - 0.1f, 0, 1.55f));
		RenderSimpleMesh(meshes["picior"], shaders["ShaderTema2"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.15f, 0, -1.55f + 0.1f));
		RenderSimpleMesh(meshes["picior"], shaders["ShaderTema2"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.15f + 2.3f - 0.1f, 0, -1.55f + 0.1f));
		RenderSimpleMesh(meshes["picior"], shaders["ShaderTema2"], modelMatrix);
	}


	//Desenare pereti;
	{
		glm::mat4 modelMatrix = glm::mat4(1);

		modelMatrix = glm::translate(modelMatrix, glm::vec3(wall1->x, wall1->y, wall1->z));
		RenderSimpleMesh(meshes["perete1"], shaders["ShaderTema2"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(wall2->x, wall2->y, wall2->z));
		RenderSimpleMesh(meshes["perete1"], shaders["ShaderTema2"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(wall3->x, wall3->y, wall3->z));
		RenderSimpleMesh(meshes["perete2"], shaders["ShaderTema2"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(wall4->x, wall4->y, wall4->z));
		RenderSimpleMesh(meshes["perete2"], shaders["ShaderTema2"], modelMatrix);
	}


	checkWallCollision();


	//Update viteza bile PENTRU TESTARE COLIZIUNE CU PERETE
	if (game->start == true) {


		//Vitezele initiale
		if (oVariab == 0)
		{

			alba->vx = power * cos(camera->aux2);
			alba->vz = -power * sin(camera->aux2);
			oVariab++;
		}

		//Am simulat si forta de frecare
		alba->ax = -alba->vx * 0.3f;
		alba->az = -alba->vz * 0.3f;




		alba->vx += alba->ax * deltaTimeSeconds;
		alba->vz += alba->az * deltaTimeSeconds;



		alba->x += alba->vx * deltaTimeSeconds;
		alba->z += alba->vz * deltaTimeSeconds;

		if (fabs(alba->vx*alba->vx + alba->vz*alba->vz) < 0.01f)
		{
			alba->vx = 0;
			alba->vz = 0;

			//Cand se opreste bila , atunci camera revine la THIRD PERSON in jurul bilei
			game->pozitionareBila = 1;
			game->tipVedere = 2;
			game->startTinta = true;
			game->start = false;
			game->runda++;
		}

	}
	else
	{
		oVariab = 0;
	}




	checkBuzunareCollision();
	{
		//Desenare bila alba
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(alba->x, alba->y, alba->z));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(alba->radius, alba->radius, alba->radius));
		if (alba->viata)
			RenderSimpleMesh(meshes["alba"], shaders["ShaderTema2"], modelMatrix);
	}

	//Desenare buzunare masa
	{
		int i;


		for (i = 0; i < 6; i++) {
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(buzunare[i]->x, buzunare[i]->y, buzunare[i]->z));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(buzunare[i]->radius, buzunare[i]->radius, buzunare[i]->radius));
			RenderSimpleMesh(meshes["buzunar"], shaders["ShaderTema2"], modelMatrix);
		}

	}

	//Desenare bile de joc
	{
		int i;
		for (i = 0; i < 15; i++) {
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(bile[i]->x, bile[i]->y, bile[i]->z));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(bile[i]->radius, bile[i]->radius, bile[i]->radius));
			if (bile[i]->color == 1)
				RenderSimpleMesh(meshes["rosie"], shaders["ShaderTema2"], modelMatrix);
			else if (bile[i]->color == 2) {
				RenderSimpleMesh(meshes["galbena"], shaders["ShaderTema2"], modelMatrix);
			}
			else
			{
				RenderSimpleMesh(meshes["buzunar"], shaders["ShaderTema2"], modelMatrix);
			}
		}

	}

	//Desenare Masa + Tac
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(masa->x, masa->y, masa->z));
		RenderSimpleMesh(meshes["masa"], shaders["ShaderTema2"], modelMatrix);



		tac->x = alba->x;
		tac->y = alba->y;
		tac->z = alba->z;



		modelMatrix = glm::mat4(1);

		modelMatrix = glm::translate(modelMatrix, glm::vec3(tac->x, tac->y, tac->z));

		modelMatrix = glm::rotate(modelMatrix, (camera->aux), glm::vec3(0, 1, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, alba->radius));

		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
		
		if (game->pozitionareBila == 1)
			RenderSimpleMesh(meshes["tac"], shaders["ShaderTema2Animatie"], modelMatrix);
	}



	//Afisare statistici 
	if (game->runda == game->oldRunda + 1)
	{
		game->jucatorActual++;
		game->jucatorActual %= 2;

		printf("Runda %d \n", game->runda);
		game->oldRunda = game->runda;



		if (game->jucatorActual + 1 == 1)
			printf("Cel care trebuie sa loveasca este JUCATORUL 1\n");
		else
			printf("Cel care trebuie sa loveasca este JUCATORUL 2\n");

		printf("\n");
		printf("Statistici Curente \n");
		printf("Faulturi JUCATOR 1 : %d \n", game->faultPlayer1);
		printf("Faulturi JUCATOR 2 : %d \n", game->faultPLayer2);
		printf("\n");
		printf("Puncte JUCATOR 1 : %d \n", game->punctePlayer1);
		printf("Puncte JUCATOR 2 : %d \n", game->punctePlayer2);
		printf("\n\n");
	}
}


void Tema2::calculateDistance(Paralelipiped *b, Ball *ball) {

	Paralelipiped* it = b;

	glm::vec2 center(ball->x, ball->z * (-1));
	glm::vec2 aabb_half_extents(it->width / 2, it->length / 2);
	glm::vec2 aabb_center(it->centerX, it->centerZ);

	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	glm::vec2 closest = aabb_center + clamped;
	difference = closest - center;



	if (glm::length(difference) < ball->radius) {

		ball->vx *= (-1);

	}
}


void Tema2::calculateDistance2(Paralelipiped *b, Ball *ball) {

	Paralelipiped* it = b;

	glm::vec2 center(ball->x, ball->z * (-1));
	glm::vec2 aabb_half_extents(it->width / 2, it->length / 2);
	glm::vec2 aabb_center(it->centerX, it->centerZ);

	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	glm::vec2 closest = aabb_center + clamped;
	difference = closest - center;



	if (glm::length(difference) < ball->radius) {


		//float sum = it->x + it->width;
		ball->vz *= (-1);

	}
}


void Tema2::checkWallCollision()
{

	calculateDistance(wall1, alba);
	calculateDistance(wall2, alba);
	calculateDistance2(wall3, alba);
	calculateDistance2(wall4, alba);

}

void Tema2::checkWallCollision2()
{

	calculateDistance(wall1, alba);
	calculateDistance(wall2, alba);
	calculateDistance2(wall3, alba);
	calculateDistance2(wall4, alba);

}


void Tema2::checkBuzunareCollision()
{
	auto DoCirclesOverlap = [](float x1, float y1, float r1, float x2, float y2, float r2)
	{
		return fabs((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)) <= (r1 + r2)*(r1 + r2);
	};

	auto IsPointInCircle = [](float x1, float y1, float r1, float px, float py)
	{
		return fabs((x1 - px)*(x1 - px) + (y1 - py)*(y1 - py)) < (r1 * r1);
	};

	std::vector<Ball*>::iterator it = buzunare.begin();
	Ball *aux;
	while (it != buzunare.end()) {

		aux = *it;
		if (DoCirclesOverlap(alba->x, alba->z, alba->radius, aux->x, aux->z, 0.035))
		{
			alba->viata = false;
		}
		++it;
	}

	if (!alba->viata) {
		printf("=====================================\n");
		printf("Jucatorul %d a introdus bila alba in buzunar (FAULT) \n", game->jucatorActual + 1);
		printf("=====================================\n");

		
		alba->x = alba->restartX;
		alba->z = alba->restartZ;
		alba->vx = alba->vz = 0;
		alba->viata = true;
		game->pozitionareBila = 0;
		game->start = false;
		game->runda++;

		if (game->jucatorActual == 0) {
			game->faultPlayer1++;
		}
		else
		{
			game->faultPLayer2++;
		}
	}


}

int firstTime = 0;
void Tema2::FrameEnd()
{



	glm::vec3 center = glm::vec3(0, 0, 0);
	if (game->startTinta == true) {
		camera->position = glm::vec3(alba->x, alba->y + 0.4f, alba->z + 0.7f);
		center = glm::vec3(alba->x, alba->y, alba->z);
		game->startTinta = false;
	}
	else
	{

		if (game->pozitionareBila == 1)
			center = glm::vec3(alba->x, alba->y, alba->z);
		else
			center = glm::vec3(0, 0, 0);
	}
	camera->Set(camera->position, center, glm::vec3(0, 1, 0));



	if (game->tipVedere == 2)
		DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
	else {
		glm::vec3 pozitie_auxiliara = glm::vec3(-0.0166988, 5.56143, 0.213683);
		glm::vec3 up_auxiliar = glm::vec3(1.10478e-07, 0.00169664, -0.999999);

		camera->Set(pozitie_auxiliara, glm::vec3(0, 0, 0), up_auxiliar);
		DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);

	}


}

void Tema2::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// TODO : get shader location for uniform mat4 "Model"
	int location;
	location = glGetUniformLocation(shader->GetProgramID(), "Model");


	// TODO : set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// TODO : get shader location for uniform mat4 "View"
	location = glGetUniformLocation(shader->GetProgramID(), "View");
	//!!!!!!!!!!! AICI TREBUIE SA FOLOSESC CAMERA 


	// TODO : set shader uniform "View" to viewMatrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// TODO : get shader location for uniform mat4 "Projection"
	location = glGetUniformLocation(shader->GetProgramID(), "Projection");

	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));



	location = glGetUniformLocation(shader->GetProgramID(), "timeSeconds");
	float timp = clock() - game->time;


	if (timp > 3350) {
		game->time = clock();

	}


	float var_aux = 3500 / 2;

	float putere = 4;
	if (timp <= var_aux) {
		this->power = putere * timp / var_aux;
	}
	else
	{
		this->power = putere * (var_aux - timp + var_aux) / var_aux;
		this->power = putere - this->power;
	}

	if (game->startPower == false)
		timp = 0;
	glUniform1f(location, (float)timp / CLOCKS_PER_SEC);
	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema2::RenderMeshColor(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, glm::vec3 color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);




	int location;
	location = glGetUniformLocation(shader->GetProgramID(), "Model");


	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	location = glGetUniformLocation(shader->GetProgramID(), "View");

	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	location = glGetUniformLocation(shader->GetProgramID(), "Projection");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	location = glGetUniformLocation(shader->GetProgramID(), "Culoare");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(color));

	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h



///Aici se misca bila la inceput +++
void Tema2::OnInputUpdate(float deltaTime, int mods)
{



	///Miscarea bilei pe tabla 
	{
		//POSIBIL SA MODIFICCC
		game->lookAtBall = false;

		if (game->pozitionareBila == 0) {
			float val = alba->z;
			float val2 = alba->x;

			if (window->KeyHold(GLFW_KEY_W)) {
				val -= 0.7 * deltaTime;
				if (val > game->limitSupZ) {
					alba->z = val;
				}
				else
				{
					alba->z = game->limitSupZ;
				}
			}
			if (window->KeyHold(GLFW_KEY_A)) {
				val2 -= 0.7 * deltaTime;
				if (val2 > game->limitInfX) {
					alba->x = val2;
				}
				else
				{
					alba->x = game->limitInfX;
				}
			}

			if (window->KeyHold(GLFW_KEY_S)) {
				val += 0.7 * deltaTime;
				if (val < game->limitInfZ) {
					alba->z = val;
				}
				else
				{
					alba->z = game->limitInfZ;
				}
			}

			if (window->KeyHold(GLFW_KEY_D)) {
				val2 += 0.7 * deltaTime;
				if (val2 < game->limitSupX) {
					alba->x = val2;
				}
				else
				{
					alba->x = game->limitSupX;
				}
			}


		}
	}

	if (game->pozitionareBila == 1)
		if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT))
		{
			if (game->startPower == false) {
				game->time = clock();
			}

			game->startPower = true;
		}
		else
		{
			if (game->startPower == true) {
				game->start = true;
				game->tipVedere = 1;
				game->pozitionareBila = 2;


			}
			game->startPower = false;

		}

}

void Tema2::OnKeyPress(int key, int mods)
{
	// add key press event


	if (key == GLFW_KEY_SPACE && game->pozitionareBila == 0)
	{
		game->tipVedere = 2;
		game->pozitionareBila = 1;
		game->startTinta = true;
	}


	if (key == GLFW_KEY_T)
	{
		renderCameraTarget = !renderCameraTarget;
	}


	if (window->KeyHold(GLFW_KEY_O)) {
		projectionMatrix = glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f, 0.01f, 20.0f);

	}

	if (window->KeyHold(GLFW_KEY_P)) {
		projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT) && game->pozitionareBila == 1)
	{
		float sensivityOX = 0.0014f;
		float sensivityOY = 0.0014f;

		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			

			camera->RotateThirdPerson_OY(sensivityOY * deltaX);
			unghi += sensivityOY * 0.1f;

		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed

			camera->RotateFirstPerson_OX(-sensivityOX * deltaY);
			camera->RotateThirdPerson_OY(-sensivityOY * deltaX);


		}

	}




}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{


}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
