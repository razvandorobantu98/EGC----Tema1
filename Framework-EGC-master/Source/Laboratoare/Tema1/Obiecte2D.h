//Dorobantu Razvan-Florin, 335CB

#pragma once

#include <string>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Obiecte2D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(std::string name, glm::vec3 color);
	Mesh* CreateCircle(std::string name, glm::vec3 color);
	Mesh* CreateTriangle(std::string name, glm::vec3 color);
}

