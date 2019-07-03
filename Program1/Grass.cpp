#include "Mesh.h"

class Grass {
	vector<Mesh> tiles;
	int floorScale;
	int tileSize;

	vector<glm::vec3> vertices;
	vector<glm::vec3> normals;
	vector<glm::vec2> uvs;

	glm::vec3 basePosition;

public:
	Grass::Grass(Shader *shader, int floorScale, int tileSize) {
		this->floorScale = floorScale;
		this->tileSize = tileSize;

		bool res = loadOBJ("Objects/floor.obj", vertices, uvs, normals);
		Mesh base = Mesh(shader, vertices, normals, uvs, "Textures/Grass01.bmp");
		base.setScale(glm::vec3(tileSize, 1.0f, tileSize));

		base.setPosition(glm::vec3(floorScale, 0.0f, floorScale));

		for (int i = 0; i < floorScale; i++)
		{
			base.move(glm::vec3(-tileSize, 0.0f, 0.0f));
			tiles.push_back(base);
			for (int i = 0; i < floorScale; i++)
			{
				base.move(glm::vec3(0.0f, 0.0f, -tileSize));
				tiles.push_back(base);
			}
			base.move(glm::vec3(0.0f, 0.0f, tileSize*floorScale));
		}
	}

	void Grass::Render(glm::mat4 view) {
		for (int i = 0; i < tiles.size(); i++)
		{
			tiles[i].Render(view);
		}
	}

};