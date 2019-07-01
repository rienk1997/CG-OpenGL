#include "Shader.h"

Shader::Shader(const char * vertexFile, const char * fragmentFile)
{
	GLuint vsh_id = makeVertexShader(vertexFile);
	GLuint fsh_id = makeFragmentShader(fragmentFile);
	// Make program
	this->id = glsl::makeShaderProgram(vsh_id, fsh_id);
}


Shader::~Shader()
{
	glDeleteProgram(this->id);
}

GLuint Shader::getShaderId()
{
	return this->id;
}

void Shader::useShader()
{
	glUseProgram(this->id);
}

void Shader::unuseShader()
{
	glUseProgram(0);
}

void Shader::set1i(GLint value, const GLchar * name)
{
	this->useShader();
	glUniform1i(glGetUniformLocation(this->id, name), value);
	this->unuseShader();
}

void Shader::setVec1f(GLfloat value, const GLchar * name)
{
	this->useShader();
	glUniform1f(glGetUniformLocation(this->id, name), value);
	this->unuseShader();
}

void Shader::setVec2f(glm::fvec2 value, const GLchar * name)
{
	this->useShader();
	glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
	this->unuseShader();
}

void Shader::setVec3f(glm::fvec3 value, const GLchar * name)
{
	this->useShader();
	glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
	this->unuseShader();
}

void Shader::setVec4f(glm::fvec4 value, const GLchar * name)
{
	this->useShader();
	glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
	this->unuseShader();
}

void Shader::setMat3fv(glm::mat3 value, const GLchar * name, GLboolean transpose)
{
	this->useShader();
	glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));
	this->unuseShader();
}

void Shader::setMat4fv(glm::mat4 value, const GLchar * name, GLboolean transpose)
{
	this->useShader();
	glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));
	this->unuseShader();
}

GLuint Shader::makeVertexShader(const char * vertexFile)
{
	// Init Vertexshader
	char * vertexshader = glsl::readFile(vertexFile);
	GLuint vsh_id = glsl::makeVertexShader(vertexshader);

	return vsh_id;
}

GLuint Shader::makeFragmentShader(const char * fragmentFile)
{
	// Init Fragshader
	char * fragshader = glsl::readFile(fragmentFile);
	GLuint fsh_id = glsl::makeFragmentShader(fragshader);

	return fsh_id;
}
