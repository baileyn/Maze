#ifndef VERTEX_HPP
#define VERTEX_HPP
#pragma once

#include <glm/vec3.hpp>

struct Vertex {
	/**
	 * @brief the position of the Vertex.
	 */
	glm::vec3 position;

	/**
	 * @brief the color of the Vertex.
	 */
	glm::vec3 color;
};

#endif // VERTEX_HPP