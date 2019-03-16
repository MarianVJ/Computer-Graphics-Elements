#include "Object3D.h"

#include <Core/Engine.h>

Mesh* Object3D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
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



//Creez un obiect 3D pentru platforma 
Mesh* Object3D::CreateParalelipiped(std::string name, glm::vec3 leftBottomCorner, float width, float height, float inaltime, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(width, 0, 0), color),
		VertexFormat(corner + glm::vec3(width, height, 0), color),
		VertexFormat(corner + glm::vec3(0, height, 0), color),

		VertexFormat(corner + glm::vec3(0,0,-inaltime), color),
		VertexFormat(corner + glm::vec3(width, 0, -inaltime), color),
		VertexFormat(corner + glm::vec3(width, height, -inaltime), color),
		VertexFormat(corner + glm::vec3(0, height, -inaltime), color)
	
	};


	Mesh* platform = new Mesh(name);
	std::vector<unsigned short> indices =
	{
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3,
	};

	platform->InitFromData(vertices, indices);
	return platform;
}

//Creez un obiect 3D pentru platforma 
Mesh* Object3D::CreateTac(std::string name, glm::vec3 leftBottomCorner, float varf, float baza, float lungime, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(varf, 0, 0), color),

		VertexFormat(corner + glm::vec3(varf, varf, 0), color),
		VertexFormat(corner + glm::vec3(0, varf, 0), color),
		

		

		VertexFormat(corner + glm::vec3((varf-baza)/2 ,(varf-baza)/2,lungime ), color),

		VertexFormat(corner + glm::vec3(varf + (baza - varf)/2, (varf-baza)/2, lungime ), color),
		VertexFormat(corner + glm::vec3((baza-varf) / 2 + varf, varf + (baza - varf) / 2, lungime ), color),
		VertexFormat(corner + glm::vec3((varf-baza)/2, varf + (baza - varf) / 2, lungime ), color)
	
	};

	

	
	Mesh* platform = new Mesh(name);
	std::vector<unsigned short> indices =
	{
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3,
	};

	platform->InitFromData(vertices, indices);
	return platform;
}
