#pragma once

#include "Mesh.h"

class IObject 
{
protected:
	glm::vec3 basePosition;
public:
	IObject(Shader *shader, glm::vec3 position) { this->basePosition = position;  };
	~IObject() {};

	virtual void Render(glm::mat4 view) = 0;
	virtual void Build(Shader* shader) = 0;
};
