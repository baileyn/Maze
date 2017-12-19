#ifndef ENTITY_HPP
#define ENTITY_HPP
#pragma once

#include <glad/glad.h>

class Entity
{
public:
	/**
	 * @brief constructs a new renderable Entity.
	 * 
	 * @param indicesCount the number of indices this Entity has.
	 * @param vao the OpenGL Vertex Array Object.
	 * @param vbo the OpenGL Vertex Buffer Object.
	 * @param ebo the OpenGL Element Buffer Object.
	 */
	Entity(size_t indicesCount, GLuint vao, GLuint vbo, GLuint ebo);

	/**
	 * @brief renders this Entity to the screen.
	 * 
	 * This function handles binding the appropriate objects and drawing.
	 */
	void render();

	/**
	 * @brief cleans up the OpenGL objects.
	 */
	void cleanup();

private:
	size_t m_indiciesCount;
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
};

#endif // ENTITY_HPP