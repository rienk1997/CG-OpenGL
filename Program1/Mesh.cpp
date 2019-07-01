#include "Mesh.h"

void Mesh::InitVao(Shader* shader)
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

Mesh::Mesh(Shader* shader, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> uvs)
{
	this->vertices = vertices;
	this->normals = normals;
	this->uvs = uvs;
	this->InitVao(shader);
}

Mesh::~Mesh()
{
}

void Mesh::Render(Shader * shader)
{
	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);
}
