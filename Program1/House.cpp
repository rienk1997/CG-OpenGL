#include "Mesh.h"

class House{
	Mesh *base;
	Mesh *roof;

	vector<glm::vec3> verticesBase;
	vector<glm::vec3> normalsBase;
	vector<glm::vec2> uvsBase;

	vector<glm::vec3> verticesRoof;
	vector<glm::vec3> normalsRoof;
	vector<glm::vec2> uvsRoof;

	glm::vec3 basePosition;

public:
	House::House(Shader *shader, glm::vec3 position) {
		basePosition = position;
		// Base
		bool res = loadOBJ("Objects/box.obj", verticesBase, uvsBase, normalsBase);
		base = new Mesh(shader, verticesBase, normalsBase, uvsBase, "Textures/Yellobrk.bmp");
		base->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		base->move(basePosition);
		// Roof
		bool res2 = loadOBJ("Objects/box.obj", verticesRoof, uvsRoof, normalsRoof);
		roof = new Mesh(shader, verticesRoof, normalsRoof, uvsRoof, "Textures/uvtemplate.bmp");
		roof->setPosition(glm::vec3(0.0f, 1.0f, 0.0f));
		roof->move(basePosition);
	}

	void House::Render(glm::mat4 view) {
		roof->Render(view);
		base->Render(view);
	}

};

