#pragma once

#include<iostream>
#include<vector>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"

#include "Shader.h"

class Mesh
{
private:
	GLuint vao;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	void InitVao(Shader* shader);
public:
	Mesh(Shader* shader, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> uvs);
	~Mesh();
	void Render(Shader* shader);
};

