#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"

class Shader
{
private:
	GLuint id;

	GLuint makeVertexShader(const char* vertexFile);
	GLuint makeFragmentShader(const char* fragmentFile);
public:
	Shader(const char* vertexFile, const char* fragmentFile);
	~Shader();

	GLuint getShaderId();

	void useShader();
	void unuseShader();

	void set1i(GLint value, const GLchar* name);

	void setVec1f(GLfloat value, const GLchar* name);
	void setVec2f(glm::fvec2 value, const GLchar* name);
	void setVec3f(glm::fvec3 value, const GLchar* name);
	void setVec4f(glm::fvec4 value, const GLchar* name);

	void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE);
	void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);
};

