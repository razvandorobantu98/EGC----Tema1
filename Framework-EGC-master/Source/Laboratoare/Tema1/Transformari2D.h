//Dorobantu Razvan-Florin, 335CB

#pragma once

#include <include/glm.h>

namespace Transformari2D
{
	// Translate matrix
	inline glm::mat3 Translate(float x, float y)
	{	
		return glm::transpose(
			glm::mat3(
				1, 0, x,
				0, 1, y,
				0, 0, 1
			)
		);
	}

	// Scale matrix
	inline glm::mat3 Scale(float scaleX, float scaleY)
	{
		return glm::transpose(
			glm::mat3(
				scaleX, 0, 0,
				0, scaleY, 0,
				0, 0, 1
			)
		);
	}

	// Rotate matrix
	inline glm::mat3 Rotate(float radians)
	{
		return glm::transpose(
			glm::mat3(
				cos(radians), -sin(radians), 0,
				sin(radians), cos(radians), 0,
				0, 0, 1
			)
		);
	}
}
