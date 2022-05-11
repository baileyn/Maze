#ifndef MESHLOADER_HPP
#define MESHLOADER_HPP
#pragma once

#include "Entity.hpp"
#include "Vertex.hpp"

#include <glad/glad.h>

#include <vector>

class MeshLoader
{
public:
	/**
	 * @brief clears any vertices and indicies still stored in the MeshLoader.
	 */
	void clear();

	/**
	 * @brief adds the specified Vertex to the MeshLoader.
	 * 
	 * If the specified Vertex already exists in the MeshLoader, it's not repeated. Instead, 
	 * the Index vector has the Vertex's index appended to it.
	 * 
	 * @param vertex the Vertex to add to the MeshLoader.
	 */
	void add(const Vertex& vertex);

	/**
	 * @brief assembles the indices and vertices into an Entity.
	 * 
	 * @return Entity the constructed Entity.
	 */
	Entity build();

private:
	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices;
};

#endif // MESHLOADER_HPP