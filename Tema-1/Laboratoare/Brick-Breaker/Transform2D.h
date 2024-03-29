#pragma once

#include <include/glm.h>
//Cu ajutorul functiilor din acest fisier 
//Se realizeaza animatiile 
namespace Transform2D
{
	// Translate matrix
	inline glm::mat3 Translate(float translateX, float translateY)
	{
		
		return glm::transpose(
			glm::mat3(1, 0, translateX,
				0, 1, translateY,
				0, 0, 1)
		);
	}

	// Scale matrix
	inline glm::mat3 Scale(float scaleX, float scaleY)
	{
		
		return glm::transpose(
			glm::mat3(scaleX, 0, 0,
				0, scaleY, 0,
				0, 0, 1)
		);
	}

	// Rotate matrix
	inline glm::mat3 Rotate(float radians)
	{
		float s = sin(radians);
		float op = s * (-1);
		float c = cos(radians);
		
		return glm::transpose(
			glm::mat3(c, op, 0,
				s, c, 0,
				0, 0, 1
			)
		);
	}
}
