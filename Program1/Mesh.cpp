#include "Mesh.h"

void Mesh::InitVao()
{
	GLuint position_id, normal_id, uv_id;
	GLuint vbo_vertices, vbo_normals, vbo_uvs;

	// vbo for vertices
	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &(vertices[0]), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// vbo for normals
	glGenBuffers(1, &vbo_normals);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &(normals[0]), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// vbo for uvs
	glGenBuffers(1, &vbo_uvs);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2),
		&uvs[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Get vertex attributes
	position_id = glGetAttribLocation(shader->getShaderId(), "position");
	normal_id = glGetAttribLocation(shader->getShaderId(), "normal");
	uv_id = glGetAttribLocation(shader->getShaderId(), "uv");

	// Allocate memory for vao
	glGenVertexArrays(1, &vao);

	// Bind to vao
	glBindVertexArray(vao);

	// Bind vertices to vao
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glVertexAttribPointer(position_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(position_id);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Bind normals to vao
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
	glVertexAttribPointer(normal_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(normal_id);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Bind uvs to vao
	glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
	glVertexAttribPointer(uv_id, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(uv_id);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Stop bind to vao
	glBindVertexArray(0);
}

Mesh::Mesh(Shader* shader, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> uvs, const char * texturePath)
{
	if (texturePath != "") {
		this->textureID = loadBMP(texturePath);
	}
	this->position = glm::vec3(0.0f);
	this->rotation = glm::vec3(0.0f);
	this->scale = glm::vec3(1.0f);

	this->shader = shader;
	this->vertices = vertices;
	this->normals = normals;
	this->uvs = uvs;
	this->InitVao();
	this->updateModelMatrix();
}

Mesh::~Mesh()
{

}

void Mesh::updateUniforms(glm::mat4 view)
{
	glm::mat4 mv = view * this->ModelMatrix;
	shader->setMat4fv(mv, "mv");
}

void Mesh::updateModelMatrix()
{
	// Reset matrix
	this->ModelMatrix = glm::mat4(1.f);
	// Translation
	this->ModelMatrix = glm::translate(this->ModelMatrix, this->position);
	// Rotate X
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	// Rotate Y
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	// Rotate Z
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	// Scale
	this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
}

void Mesh::setPosition(const glm::vec3 position)
{
	this->position = position;
}

void Mesh::setRotation(const glm::vec3 rotation)
{
	this->rotation = rotation;
}

void Mesh::setScale(const glm::vec3 scale)
{
	this->scale = scale;
}

void Mesh::move(const glm::vec3 position)
{
	this->position += position;
}

void Mesh::rotate(const glm::vec3 rotation)
{
	this->rotation += rotation;
}

void Mesh::scaleMesh(const glm::vec3 scale)
{
	this->scale += scale;
}

void Mesh::Render(glm::mat4 view)
{
	this->updateModelMatrix();
	this->updateUniforms(view);

	shader->useShader();

	if (this->textureID) {
		glBindTexture(GL_TEXTURE_2D, this->textureID);
	}
	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);
	if (this->textureID) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	shader->unuseShader();

}
