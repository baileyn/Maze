#ifndef ENTITY_HPP
#define ENTITY_HPP
#pragma once

#include <glad/glad.h>

class Entity
{
public:
	Entity(size_t indicesCount, GLuint vao, GLuint vbo, GLuint ebo);

	void render();
	void cleanup();

private:
	size_t m_indiciesCount;
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
};

#endif // ENTITY_HPP