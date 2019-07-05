#include "IObject.h"

class House: public IObject{
	Mesh *base;
	Mesh *roof;

	vector<glm::vec3> verticesBase;
	vector<glm::vec3> normalsBase;
	vector<glm::vec2> uvsBase;

	vector<glm::vec3> verticesRoof;
	vector<glm::vec3> normalsRoof;
	vector<glm::vec2> uvsRoof;

public:
	House::House(Shader *shader, glm::vec3 position):IObject(shader, position) {
		this->Build(shader);
	}

	void House::Build(Shader* shader) {
		// Base
		bool res = loadOBJ("Objects/box.obj", verticesBase, uvsBase, normalsBase);
		base = new Mesh(shader, verticesBase, normalsBase, uvsBase, "Textures/Yellobrk.bmp");
		base->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		base->move(basePosition);
		// Roof
		bool res2 = loadOBJ("Objects/car.obj", verticesRoof, uvsRoof, normalsRoof);
		roof = new Mesh(shader, verticesRoof, normalsRoof, uvsRoof, "Textures/red.bmp");
		roof->setScale(glm::vec3(0.05));
		roof->setPosition(glm::vec3(0.0f, 1.0f, 0.0f));
		roof->move(basePosition);
	}

	void House::Render(glm::mat4 view) {
		roof->Render(view);
		base->Render(view);
	}

	void House::Move(glm::vec3 direction) {
		roof->move(direction);
		base->move(direction);
	}
};

