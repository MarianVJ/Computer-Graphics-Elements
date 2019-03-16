#pragma once

#include <include/glm.h>

namespace Transform3D
{
	// Translate matrix
	inline glm::mat4 Translate(float tx, float ty, float tz)
	{
		return glm::transpose(
			glm::mat4(1, 0, 0, tx,
				0, 1, 0, ty,
				0, 0, 1, tz,
				0, 0, 0, 1)
		);
	}

	// Scale matrix
	inline glm::mat4 Scale(float scaleX, float scaleY, float scaleZ)
	{
		

		return glm::transpose(
			glm::mat4(scaleX, 0, 0, 0,
					  0, scaleY, 0, 0,
				      0, 0, scaleZ, 0,
					  0, 0, 0, 1)
		);
	}

	// Rotate matrix relative to the OZ axis
	inline glm::mat4 RotateOZ(float radians)
	{
		float cosi = cos(radians);
		float sini = sin(radians);
		float negsin = (-1) * sini;

		return glm::transpose(
			glm::mat4(cosi, negsin, 0, 0,
					  sini, cosi, 0, 0,
				      0, 0, 1, 0,
					  0, 0, 0, 1)
		);
	}

	// Rotate matrix relative to the OY axis
	inline glm::mat4 RotateOY(float radians)
	{
		float cosi = cos(radians);
		float sini = sin(radians);
		float negsin = (-1) * sini;

		return glm::transpose(
			glm::mat4(cosi, 0, sini, 0,
					  0, 1, 0, 0,
					  negsin, 0, cosi, 0,
					  0, 0, 0, 1)
		);
	}

	// Rotate matrix relative to the OX axis
	inline glm::mat4 RotateOX(float radians)
	{
		float cosi = cos(radians);
		float sini = sin(radians);
		float negsin = (-1) * sini;

		return glm::transpose(
			glm::mat4(1, 0, 0, 0,
				 	  0, cosi, negsin, 0,
					  0, sini, cosi, 0,
					  0, 0, 0, 1)
		);
	}
}
