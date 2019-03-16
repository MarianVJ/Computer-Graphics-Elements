#include "Object2D.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};
	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

//Creez un obiect 2D pentru platforma 
Mesh* Object2D::CreatePlatform(std::string name, glm::vec3 leftBottomCorner, float height, float width, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(height, 0, 0), color),
		VertexFormat(corner + glm::vec3(height, width, 0), color),
		VertexFormat(corner + glm::vec3(0, width, 0), color)
	};
	Mesh* platform = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 0 , 2 };
	platform->InitFromData(vertices, indices);
	return platform;
}
//Creez un obiect 2D pentru cerc
Mesh* Object2D::CreateCircle(std::string name, glm::vec3 centerPos, float radius, glm::vec3 color)
{
	//N este numarul de puncte prin care desenam cercul
	int N = 10000;

	glm::vec3 center = centerPos;
	std::vector<VertexFormat> vertices;
	
	vertices.push_back(VertexFormat(center, color));

	int i;
	float x, y, angle;

	float twicePi = 2 * M_PI;
	for (i = 0; i < N; i++) {
		vertices.push_back(VertexFormat(center + glm::vec3(radius * sin(i * twicePi / N),radius * cos(i * twicePi / N), 0 ) , color));
	}
	Mesh* platform = new Mesh(name);

	//Indicies
	std::vector<unsigned short> indices;
	for (i = 1; i <= N; i++) {
		indices.push_back(i);
		indices.push_back(0);
		indices.push_back(i+1);
	}
	platform->InitFromData(vertices, indices);
	return platform;
}