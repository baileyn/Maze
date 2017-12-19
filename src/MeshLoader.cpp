#include "MeshLoader.hpp"

#include <algorithm>

void MeshLoader::clear()
{
	m_vertices.clear();
}

void MeshLoader::add(const Vertex& vertex)
{
	auto idx = std::find_if(std::begin(m_vertices), std::end(m_vertices), [&vertex](const Vertex& v) {
		return v.color.x == vertex.color.x && v.color.y == vertex.color.y && v.color.z == vertex.color.z &&
			v.position.x == vertex.position.x && v.position.y == vertex.position.y && v.position.z == vertex.position.z;
	});

	if (idx == std::end(m_vertices)) {
		// If the vertex wasn't found, add it to the vertices.
		m_vertices.push_back(vertex);

		// Add the new index to the indices.
		m_indices.push_back(m_vertices.size() - 1);
	}
	else {
		// If it was found, add a new entry for the index.
		size_t location = idx - std::begin(m_vertices);
		m_indices.push_back(location);


	}
}

Entity MeshLoader::build()
{
	GLuint vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(m_indices[0]), m_indices.data(), GL_STATIC_DRAW);
	
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(m_vertices[0]), m_vertices.data(), GL_STATIC_DRAW);
	
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);
	}
	glBindVertexArray(0);

	return Entity{ m_indices.size(), vao, vbo, ebo };
}