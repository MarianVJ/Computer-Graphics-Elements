#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);


	Mesh* CreatePlatform(std::string name, glm::vec3 leftBottomCorner, float height, float width,glm::vec3 color);

	Mesh* CreateCircle(std::string name, glm::vec3 centerPos, float radius, glm::vec3 color);

}

