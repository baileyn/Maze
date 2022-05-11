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
	void clear();
	void add(const Vertex& vertex);
	Entity build();

private:
	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices;
};

#endif // MESHLOADER_HPP