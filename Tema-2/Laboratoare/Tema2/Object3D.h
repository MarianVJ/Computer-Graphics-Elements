#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object3D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);


	//Mesh* CreatePlatform(std::string name, glm::vec3 leftBottomCorner, float height, float width,glm::vec3 color);
	Mesh* CreateParalelipiped(std::string name, glm::vec3 leftBottomCorner, float height, float width,float inaltime,glm::vec3 color);
	Mesh* CreateTac(std::string name, glm::vec3 leftBottomCorner, float varf, float baza, float lungime, glm::vec3 color);


}

