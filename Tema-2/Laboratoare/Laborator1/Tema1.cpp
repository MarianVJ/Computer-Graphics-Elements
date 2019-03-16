#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"
#include "Brick.h"

using namespace std;
int restartt = 1;
int squareSize;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;


	////De aici am completat cu informatii pentru tema 

	//Instantiez obiectele specifice pentru JOC, BILA si PLATFORMA
	game = new Game( resolution.x,resolution.y);
	ball = new Ball(resolution.x / 2 - 105, 50);
	platform = new Platform(resolution.x / 2 - 105, 35);

	//Creez obiectul de tip platforma ( care va aparea la inceputul jocului)
	Mesh* platformm = Object2D::CreatePlatform("platform", corner, platform->width, platform->height, glm::vec3(0, 1, 0));
	AddMeshToList(platformm);


	//De fiecare data cand se mai acumuleaza un bonus platforma va avea culoarea lui
	platformm = Object2D::CreatePlatform("platform1", corner, platform->width, platform->height, glm::vec3(0, 0, 1));
	AddMeshToList(platformm);

	platformm = Object2D::CreatePlatform("platform2", corner, platform->width, platform->height, glm::vec3(1, 1, 0));
	AddMeshToList(platformm);

	platformm = Object2D::CreatePlatform("platform3", corner, platform->width, platform->height, glm::vec3(1, 0, 0));
	AddMeshToList(platformm);


	//Creeam cele 3 patrate pentru fiecare tip de bonus
	Mesh* powerup = Object2D::CreatePlatform("powerup1", corner, 20, 20, glm::vec3(0, 0, 1));
	AddMeshToList(powerup);

	powerup = Object2D::CreatePlatform("powerup2", corner, 20, 20, glm::vec3(1, 1, 0));
	AddMeshToList(powerup);

	powerup = Object2D::CreatePlatform("powerup3", corner, 20, 20, glm::vec3(1, 0, 0));
	AddMeshToList(powerup);
	
	//Initializez obiectele din vectorul meu de caramizi 
	//Prima caramida se va situa la 200,200 
	this->initBricks(200, 200);


	//Fiecare caramida are 4 vieti , si pe masura ce este "slabita", culoarea se deschide 
	//Caramida care are nevoie de o singura lovitura pt a putea fi sparta fiind de aceeasi culoare ca si mingea
	Mesh* brick = Object2D::CreatePlatform("brick3", corner, bricks[1]->width, bricks[1]->height, glm::vec3(0.4f, 0, 0.4f));
	AddMeshToList(brick);

	brick = Object2D::CreatePlatform("brick2", corner, bricks[1]->width, bricks[1]->height, glm::vec3(0.6f, 0, 0.6f));
	AddMeshToList(brick);

	brick = Object2D::CreatePlatform("brick1", corner, bricks[1]->width, bricks[1]->height, glm::vec3(0.8f, 0, 0.8f));
	AddMeshToList(brick);

	brick = Object2D::CreatePlatform("brick", corner, bricks[1]->width, bricks[1]->height, glm::vec3(1, 0, 1));
	AddMeshToList(brick);

	//Initializam peretii conform cu coordonatele lor si dimensiunile (lungimii si latimii)
	this->initWalls();

	//Pereti laterali
	Mesh* wall = Object2D::CreatePlatform("wall1", corner, wall1->width, wall1->height, glm::vec3(0, 1, 0));
	AddMeshToList(wall);

	//Pereti laterali de culoare ca ultimul powerup
	wall = Object2D::CreatePlatform("wall11", corner, wall1->width, wall1->height, glm::vec3(0, 0, 1));
	AddMeshToList(wall);

	wall = Object2D::CreatePlatform("wall12", corner, wall1->width, wall1->height, glm::vec3(1, 1, 0));
	AddMeshToList(wall);

	wall = Object2D::CreatePlatform("wall13", corner, wall1->width, wall1->height, glm::vec3(1, 0, 0));
	AddMeshToList(wall);

	//Perete orizontal;
	wall = Object2D::CreatePlatform("wall2", corner, wall3->width, wall3->height, glm::vec3(0, 1, 0));
	AddMeshToList(wall);


	//Pereti orizontali de culoare cu ultimul powerup
	wall = Object2D::CreatePlatform("wall21", corner, wall3->width, wall3->height, glm::vec3(0, 0, 1));
	AddMeshToList(wall);

	wall = Object2D::CreatePlatform("wall22", corner, wall3->width, wall3->height, glm::vec3(1, 1, 0));
	AddMeshToList(wall);

	wall = Object2D::CreatePlatform("wall23", corner, wall3->width, wall3->height, glm::vec3(1, 0, 0));
	AddMeshToList(wall);
	
	//Exista un disc de cerc mic cu care se porneste 
	Mesh* cerc = Object2D::CreateCircle("ball", corner, ball->radius, glm::vec3(1, 0, 1));
	AddMeshToList(cerc);
	//Si unul cu o raza de doua ori si jumatate mai mare , care poate fi obitnuta in
	//urma prinderii unui powerup
	cerc = Object2D::CreateCircle("superball", corner, ball->radius * 2.5f, glm::vec3(1, 0, 1));
	AddMeshToList(cerc);
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}




void Tema1::Update(float deltaTimeSeconds)
{
	

	//Verific COliziuni bila - pereti / caramizi
	//Verific coliziuni platforma - bila / bonusuri ???? UNde mai exact 
	
	//Trebuie sa modific astfel incat sa se adapteze 

	//Verific coliziune bila caramizi
	this->collision();
	//Verific coliziuni bila Pereti Permanenti
	this->checkWallCollision();


	//Actualizez pozitia paltformei in conformitat cu cea a mousului
	if (platform->sw > 0) {
		platform->sw = 0;
		if (platform->dx > 0)
			platform->x = platform->mx - 105;
		else
		{
			platform->x = platform->mx -  105;
		}
	}

	//Am implementat 2 functii de coliziune a bilei cu platforma 
	this->checkPlatformCollision2();
	//Verific Coliziunile dintre Powerupuri si Platforma
	this->checkPlatformPowerupCollision();

	
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(platform->x, platform->y);

	//In functie de ce bonus este activat platforma ia culoarea , sau verde daca 
	//nu avem bonusuri activate
	if(game->lastbonus == 1)
		RenderMesh2D(meshes["platform1"], shaders["VertexColor"], modelMatrix);
	else if (game->lastbonus == 2)
		RenderMesh2D(meshes["platform2"], shaders["VertexColor"], modelMatrix);
	else if (game->lastbonus == 3)
		RenderMesh2D(meshes["platform3"], shaders["VertexColor"], modelMatrix);
	else
		RenderMesh2D(meshes["platform"], shaders["VertexColor"], modelMatrix);

	//Daca bila nu a fost lansata ea va urmari mijlocul platformei 
	//(sau daca a parasit scena)
	if (ball->start == 0) {
		ball->x = platform->x + (float)platform->width / 2;
		ball->y = platform->y + 45;
	}
	else
	{
		//Altfel se va deplasa prin scena 
		ball->x += ball->speedX * deltaTimeSeconds;
		ball->y += ball->speedY * deltaTimeSeconds;
	}

	//Verific anumtie conditii speciale din joc
	this->checkGameConditions();
	//Desenez powerupurile alaturi de animatia specifica
	this->drawPowerups(deltaTimeSeconds);
	//Desenez bila si vietile
	this->drawBallandLifes();
	//Desenez peretii
	this->drawWalls();
	//Desenez Caramizile sau animatiile atunci cand sunt distruse
	this->printBricks(deltaTimeSeconds);
}

//Aceasta metoda deseneaza Bila si Vietile
void Tema1::drawBallandLifes(){

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(ball->x, ball->y);
	
	//Verific daca este activata superputerea de augumentare a "bilei"
	if(!game->type1)
		RenderMesh2D(meshes["ball"], shaders["VertexColor"], modelMatrix);
	else
		RenderMesh2D(meshes["superball"], shaders["VertexColor"], modelMatrix);

	float x_aux = 15;
	float y_aux = 40;
	//Desenez cate vieti mai are jocatorul
	for (int i = 0; i < game->lifes; i++) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(x_aux, y_aux);
		RenderMesh2D(meshes["ball"], shaders["VertexColor"], modelMatrix);
		x_aux += ball->initialRadius + 20 ;
	}
}


//Aceasta metoda verifica daca trebuie ca jocul sa se reia ( playerul a castigat
//sau a ramas fara vieti actualiand anumite variabile ce tin de joc in conformitate.
void Tema1::checkGameConditions()
{
	//Verific daca Bila a parasit zona prin una din cele 3 parti posibile , si reduc numarul de vieti
	if (ball->x > game->width || ball->x < 0 || ball->y < 0 ) {
		game->lifes--;
		ball->start = 0;
		ball->speedY = 270;
		ball->speedX = 0;
		//De asemenea se pierd odata cu bila si powerupurile prinse
		//Insa cele care inca sunt in scena mai pot fi prinse
		game->type2 = false;
		game->type3 = false;
		game->type1 = false;
		game->lastbonus = 0;
		ball->radius = ball->initialRadius;
	}

	//Daca s-a pierdut si ultima viata jocul se reia
	if (game->lifes == 0 || game->destroyedBalls == 120) {

		ball->start = 0;
		ball->speedY = 270;
		ball->speedX = 0;

		game->type2 = false;
		game->type3 = false;
		game->type1 = false;
		game->lastbonus = 0;
		ball->radius = ball->initialRadius;
		game->destroyedBalls = 0;

		game->lifes = 3;
		std::vector<Brick*>::iterator it = bricks.begin();
		//Refac starea caramizilor
		while (it != bricks.end()) {
			//Refacem variabilele din caramida ce tin de scalare, respectiv
			//Daca aceasta a fost distrusa sau nu 
			(*it)->destroyed = false;
			(*it)->scale = 1;
			(*it)->bricklifes = 4;
			++it;
		}

	}

	//Daca a fost o prins un patratel pentru primul poweup care augumenteaza bila
	if (game->type1) {
		double duration;
		duration = (std::clock() - game->start1) / (double)CLOCKS_PER_SEC;
		//Verific daca a expirat
		if (duration < 30) {
			ball->radius = 2.5f * ball->initialRadius;
		}
		else
		{
			ball->radius = ball->initialRadius;
			game->type1 = false;
			if (game->lastbonus == 1)
				game->lastbonus = 0;
		}
	}

	//Powerup-ul 2 face ca bila sa nu se mai reflecteze la coliziunea cu o caramida
	if (game->type2) {
		double duration;
		duration = (std::clock() - game->start2) / (double)CLOCKS_PER_SEC;
		if (duration > 30) {
			game->type2 = false;
			if (game->lastbonus == 2)
				game->lastbonus = 0;
		}
	}

	//Powerup-ul 3 mai introduce timp de 30 sec un perete partea de jos a scenei
	if (game->type3) {
		double duration;
		duration = (std::clock() - game->start3) / (double)CLOCKS_PER_SEC;
		if (duration > 30) {
			game->type3 = false;
			if (game->lastbonus == 3)
				game->lastbonus = 0;
		}
		else
		{
			calculateDistance(wall4);
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(wall4->x, wall4->y);

			if (game->lastbonus == 1)
				RenderMesh2D(meshes["wall21"], shaders["VertexColor"], modelMatrix);
			else if (game->lastbonus == 2)
				RenderMesh2D(meshes["wall22"], shaders["VertexColor"], modelMatrix);
			else if (game->lastbonus == 3)
				RenderMesh2D(meshes["wall23"], shaders["VertexColor"], modelMatrix);
			else
				RenderMesh2D(meshes["wall2"], shaders["VertexColor"], modelMatrix);
		}
	}
}


//Metoda care verifica coliziunea dintre platforma si patratelele 
//corespunzatoare powerup-urilor
void Tema1::checkPlatformPowerupCollision() {

	std::vector<Powerup*>::iterator it = powerups.begin();
	Powerup *aux;

	while (it != powerups.end()) {
		aux = *it;

		//Pentru ca un patrat powerup sa faca coliziune cu platform
		//trebuie ca sa se "intrepatrunda" ( nu doar sa aibe in comun o axa)
		bool colX = aux->x + aux->height >= platform->x && platform->x + platform->width >= aux->x;
		bool colY = aux->y + aux->height >= platform->y && platform->y + platform->height >= aux->y;
		bool colision = colX && colY;

		if (colision) {
			//TIMPUL CAT DUREAZA  = 30 sec de la prindere
			if (aux->type == 1) {
				game->type1 = true;
				game->start1 = std::clock();
				game->lastbonus = 1;
			}

			if (aux->type == 2) {
				game->type2 = true;
				game->start2 = std::clock();
				game->lastbonus = 2;
			}

			if (aux->type == 3) {
				game->type3 = true;
				game->start3 = std::clock();
				game->lastbonus = 3;
			}
			it = powerups.erase(it);
		}
		else
		{ 
			++it;
		}
	}
}

//Metoda 2 care verifica coliziunea dintre bila si platforma
//si realizeaza reflexia corespunzator
void Tema1::checkPlatformCollision2() {

	//Centrul bilei
	glm::vec2 center(ball->x, ball->y);
	glm::vec2 aabb_half_extents(platform->width / 2, platform->height / 2);
	//Centrul Platformei
	glm::vec2 aabb_center(platform->x + platform->width / 2, platform->y + platform->height / 2);

	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	//Coordonatele punctului cel mai apropiat de cerc
	glm::vec2 closest = aabb_center + clamped;
	difference = closest - center;
	//Daca distanta de la centrul cercului la acest punct proxim
	//este mai mica decat raza atunci s-a produs coliziune
	if (glm::length(difference) < ball->radius) {

		//Bila se reflecta doar daca se ciocneste cu partea de sus 
		if ((closest.y == platform->y + platform->height && ball->speedY < 0)) {

			//Vechile constante pt viteza
			glm::vec2 oldvelocity(ball->speedX, ball->speedY);

			//Unghiul 
			float alfa = (closest.x - platform->x - 105) / 105 * M_PI / 2;
			ball->speedY *= -1;
			ball->speedX = sin(alfa) * 270;
			//Noua viteza 
			glm::vec2 velocity(ball->speedX, ball->speedY);
			//Pe care o normalizam
			velocity = glm::normalize(velocity) *glm::length(oldvelocity);
			
			ball->speedX = velocity.x;
			ball->speedY = velocity.y;
		}
	}
}

//Aceeasi metoda precum cea de mai sus ( doar ca implementata diferit)
//A fost utilizata , momentan nu este apelata in program
void Tema1::checkPlatformCollision() {

	glm::vec2 center(ball->x, ball->y);
	glm::vec2 aabb_half_extents(platform->width / 2, platform->height / 2);
	glm::vec2 aabb_center(platform->x + platform->width / 2, platform->y + platform->height / 2);

	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	glm::vec2 closest = aabb_center + clamped;
	difference = closest - center;

	if (glm::length(difference) < ball->radius) {
		if ((closest.y == platform->y + platform->height && ball->speedY < 0)) {
			float alfa = (closest.x - platform->x - 105) / 105 * M_PI / 2;
			ball->speedY *= -1;
			ball->speedX = sin(alfa) * 200 ;
		}
	}
}

//Aceasta metoda calculeaza distanta de la bila la o variabile
//de tip Brick, dar ea este apelata doar pt a verifica coliziunile cu 
//cei 4 pereti ( 3 permanenti si unul temporar)
void Tema1::calculateDistance(Brick* b) {

	Brick* it = b;
	glm::vec2 center(ball->x, ball->y);
	glm::vec2 aabb_half_extents(it->width /  2, it->height / 2) ;
	glm::vec2 aabb_center(it->centerX, it->centerY);

	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	glm::vec2 closest = aabb_center + clamped;
	difference = closest - center;

	if (glm::length(difference) < ball->radius) {
		if ((closest.y == it->y  && ball->speedY > 0) || (closest.y == it->y + it->height && ball->speedY < 0)) {
				ball->speedY *= (-1);
		}
		if((closest.x == it->x  && ball->speedX > 0) || (closest.x == it->x + it->width && ball->speedX < 0))
		{
				ball->speedX *= (-1);
		}
	}
}

//Verifica coliziunea cu peretii initiali din scena
void Tema1::checkWallCollision(){
	calculateDistance(wall1);
	calculateDistance(wall2);
	calculateDistance(wall3);
}

//Aceasta metoda verifica coliziunea cea mai des intalnita si cea mai IMPORTANTA
//dintre bila si caramizi
void Tema1::collision()
{
	Brick* it;
	std::vector<Brick*>::iterator itt = bricks.begin();
	int swx = 0;
	int swy = 0;

	while (itt != bricks.end()) {
		it = *itt;
		glm::vec2 center(ball->x, ball->y);
		glm::vec2 aabb_half_extents(25, 15);
		glm::vec2 aabb_center(it->centerX, it->centerY);

		glm::vec2 difference = center - aabb_center;
		glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
		glm::vec2 closest = aabb_center + clamped;
		difference = closest - center;
		
		//Verific daca s-a produs coliziunea
		if (glm::length(difference) < ball->radius && !it->destroyed) {
			int sw_aux = 0;
			
			//Daca s-a produs pe fata de sus sau de jos a caramizii
			if ((closest.y == it->y  && (ball->speedY > 0 || swy > 0)) || (closest.y == it->y + it->height && (ball->speedY < 0 || swy > 0))) {
				
				//Daca al doilea powerup implementat nu este activat bila ricoseaza
				if(!game->type2 && swy == 0)
					ball->speedY *= (-1);

				sw_aux = 1;
				//Daca al doilea powerup e activat bila este distrusa indefernt de cate
				//ciocniri mai erau necesare pt a fi doborata
				if (game->type2) {
					it->destroyed = true;
				}
				else
					it->bricklifes--;

				//Daca a fost distrusa "clasic" , marchez acest eveniment
				if(it->bricklifes == 0)
					it->destroyed = true;	

				//Exista 10% sanse ca o un powerup sa apara la distrugerea unei caramizi
				//Iar din sansele ca sa apartina unuia dintre bonusuri sunt egale
				if (rand() % 7 == 0 && it->destroyed) {
					powerups.push_back(new Powerup(it->x + ((it->width - 20) / 2), it->y, rand() % 3 + 1));
					
				}
				swy++;
			}


			if ((closest.x == it->x  && (ball->speedX > 0 || swx > 0)) || (closest.x == it->x + it->width && (ball->speedX < 0 || swx > 0)))
			{
				//Daca al doilea poweup implementat nu este activat bila ricoseaza
				if (!game->type2 && swx == 0)
					ball->speedX *= (-1);
	
				//VERIFIC CONDITIE POWERUP	
				if (game->type2) {
					it->destroyed = true;
				}
				else
				{
					//Daca s-a intrat si in bucla precedenta , asta inseamna ca bila
					//loveste caramida fix inntr-un colt si se va intoarce pe aceeasi directie
					//dar sens opus de unde a venit , si nu se va mai distruge inca un scut
					if (sw_aux == 0)
						it->bricklifes--;
				}

				if (it->bricklifes == 0)
					it->destroyed = true;

				//De asemenea 10% sanse 
				if (rand() % 7 == 0 && sw_aux == 0 && it->destroyed) {
					powerups.push_back(new Powerup(it->x + ((it->width - 20) / 2), it->y, rand() % 3 + 1));
				}
				swx++;
				
			}
			//Daca caramida curenta a fost distrusa marchez la nivel "global"
			if (it->destroyed)
				game->destroyedBalls++;
		}
		itt++;
	}
}



//Metoda care deseneaza peretii
void Tema1::drawWalls()
{
	
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(wall1->x, wall1->y);
	if (game->lastbonus == 1)
		RenderMesh2D(meshes["wall11"], shaders["VertexColor"], modelMatrix);
	else if (game->lastbonus == 2)
		RenderMesh2D(meshes["wall12"], shaders["VertexColor"], modelMatrix);
	else if (game->lastbonus == 3)
		RenderMesh2D(meshes["wall13"], shaders["VertexColor"], modelMatrix);
	else
		RenderMesh2D(meshes["wall1"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(wall2->x, wall2->y);
	if (game->lastbonus == 1)
		RenderMesh2D(meshes["wall11"], shaders["VertexColor"], modelMatrix);
	else if (game->lastbonus == 2)
		RenderMesh2D(meshes["wall12"], shaders["VertexColor"], modelMatrix);
	else if (game->lastbonus == 3)
		RenderMesh2D(meshes["wall13"], shaders["VertexColor"], modelMatrix);
	else
		RenderMesh2D(meshes["wall1"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(wall3->x, wall3->y);
	if (game->lastbonus == 1)
		RenderMesh2D(meshes["wall21"], shaders["VertexColor"], modelMatrix);
	else if (game->lastbonus == 2)
		RenderMesh2D(meshes["wall22"], shaders["VertexColor"], modelMatrix);
	else if (game->lastbonus == 3)
		RenderMesh2D(meshes["wall23"], shaders["VertexColor"], modelMatrix);
	else
		RenderMesh2D(meshes["wall2"], shaders["VertexColor"], modelMatrix);
}



void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{

}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}


//Pozitia platformei se actualizeaza la fiecare miscare a mouse-ului
void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	platform->mx = (float) mouseX;
	platform->my = (float)mouseY;
	platform->dx = (float)deltaX;
	platform->dy = (float)deltaY;
	platform->sw = 1;
}


//Click stanga si bila este lansata
void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT))
	{
		ball->start += 1;
		
	}
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}

//Metoda care intializeaza pozitiile celor 4 pereti
void Tema1::initWalls() {
	
	//Peretele stanga
	wall1 = new Brick(0,100, window->GetResolution().y, 25);

	//Perete dreapta
	wall2 =  new Brick(window->GetResolution().x - 25, 100, window->GetResolution().y,25);

	//Perete sus
	wall3 = new Brick(0, window->GetResolution().y - 25, 25, window->GetResolution().x);


	//Perete de jos care se activeaza la un powerup
	wall4 = new Brick(0, 0, 25, window->GetResolution().x);

}

//Metoda care initializaza pozitiile caramizilor (120 in acest caz), 
//precum si dimensiunile acestora 
void Tema1::initBricks(float firstX, float firstY)
{
	int line = 10;
	int elem = 12;

	float pozY = firstX;
	float pozxx = firstY;

	int i;
	int j;
	for (i = 0; i < line; i++) {
		for (j = 0; j < elem; j++) {
			bricks.push_back(new Brick(pozxx, pozY,30,50));
			pozxx += 70;
		}
		pozY += 40;
		pozxx = firstY;
	}
}

//Metoda care deseneaza powerup-urile si animatia specifica
void Tema1::drawPowerups(float deltaTimeSeconds) {

	std::vector<Powerup*>::iterator it = powerups.begin();
	Powerup *aux;

	while (it != powerups.end()) {
		aux  = *it;
		if (aux->y + aux->height < 0) {
			it = powerups.erase(it);
		}
		else
		{
			aux->y -= deltaTimeSeconds * 60;
			aux->angle += M_PI / 60;
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(aux->x, aux->y);

			modelMatrix *= Transform2D::Translate(aux->height / 2, aux->height / 2);
			modelMatrix *= Transform2D::Rotate(aux->angle);
			modelMatrix *= Transform2D::Translate(-aux->height / 2, -aux->height / 2);

			if(aux->type == 1)
				RenderMesh2D(meshes["powerup1"], shaders["VertexColor"], modelMatrix);
			if(aux->type == 2)
				RenderMesh2D(meshes["powerup2"], shaders["VertexColor"], modelMatrix);

			if (aux->type == 3)
				RenderMesh2D(meshes["powerup3"], shaders["VertexColor"], modelMatrix);
			++it;
		}
	}
}

//Metoda care deseneaza Caramizile si animatiile specifice de disparitie
//la distrugerea lor
void Tema1::printBricks(float deltaTimeSeconds)
{
	modelMatrix = glm::mat3(1);
	std::vector<Brick*>::iterator it = bricks.begin();

	while (it != bricks.end()) {
		if (!(*it)->destroyed) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate((*it)->x, (*it)->y);
			if((*it)->bricklifes == 1)
				RenderMesh2D(meshes["brick"], shaders["VertexColor"], modelMatrix);
			else if ((*it)->bricklifes == 2)
				RenderMesh2D(meshes["brick1"], shaders["VertexColor"], modelMatrix);
			else if ((*it)->bricklifes == 3)
				RenderMesh2D(meshes["brick2"], shaders["VertexColor"], modelMatrix);
			else if ((*it)->bricklifes == 4)
				RenderMesh2D(meshes["brick3"], shaders["VertexColor"], modelMatrix);
		}
		else
		{
			//In acest loc creez efectul de disparitie treptata 
			if ((*it)->scale > 0) {
				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate((*it)->x, (*it)->y);
				(*it)->scale -= 1.27f * deltaTimeSeconds;
				modelMatrix *= Transform2D::Translate((*it)->width/2, (*it)->height/2);
				modelMatrix *= Transform2D::Scale((*it)->scale,(*it)->scale);
				modelMatrix *= Transform2D::Translate(-(*it)->width / 2, -(*it)->height / 2);
				
				 if ((*it)->bricklifes == 2)
					RenderMesh2D(meshes["brick1"], shaders["VertexColor"], modelMatrix);
				else if ((*it)->bricklifes == 3)
					RenderMesh2D(meshes["brick2"], shaders["VertexColor"], modelMatrix);
				else if ((*it)->bricklifes == 4)
					RenderMesh2D(meshes["brick3"], shaders["VertexColor"], modelMatrix);
				else
					RenderMesh2D(meshes["brick"], shaders["VertexColor"], modelMatrix);
			}
		}
		++it;
	}
}
