#include"IObject.h"

class Windmill : public IObject {

	Mesh* base;
	Mesh* mill;

	vector<glm::vec3> verticesBase;
	vector<glm::vec3> normalsBase;
	vector<glm::vec2> uvsBase;

	vector<glm::vec3> verticesMill;
	vector<glm::vec3> normalsMill;
	vector<glm::vec2> uvsMill;
public:
	Windmill::Windmill(Shader* shader, glm::vec3 position):IObject(shader, position) 
	{
		this->Build(shader);
	}

	void Render(glm::mat4 view)
	{
		base->Render(view);
		mill->rotate(glm::vec3(0.0f, 0.0f, 1.0f));
		mill->Render(view);
	}

	void Build(Shader * shader)
	{
		// Base
		bool res = loadOBJ("Objects/cylinder32.obj", verticesBase, uvsBase, normalsBase);
		base = new Mesh(shader, verticesBase, normalsBase, uvsBase, "Textures/windmill.bmp");
		base->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		base->move(basePosition);
		base->setScale(glm::vec3(0.3f, 6.0f, 0.3f));

		// Mill
		bool res2 = loadOBJ("Objects/windmill.obj", verticesMill, uvsMill, normalsMill);
		mill = new Mesh(shader, verticesMill, normalsMill, uvsMill, "Textures/windmill.bmp");
		mill->setPosition(glm::vec3(0.0f, 6.0f, -0.5f));
		mill->move(basePosition);
		mill->setScale(glm::vec3(0.03f));
	}
};