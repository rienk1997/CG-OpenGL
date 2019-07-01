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
	Shader* shader;
	GLuint vao;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 ModelMatrix;

	void InitVao();

	void updateUniforms(glm::mat4 view);
	void updateModelMatrix();
public:
	Mesh(Shader* shader, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> uvs);
	~Mesh();

	void setPosition(const glm::vec3 position);
	void setRotation(const glm::vec3 rotation);
	void setScale(const glm::vec3 scale);

	void move(const glm::vec3 position);
	void rotate(const glm::vec3 rotation);
	void scaleMesh(const glm::vec3 scale);

	void Render(glm::mat4 view);
};

