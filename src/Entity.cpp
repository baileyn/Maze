#include "Entity.hpp"

Entity::Entity(size_t indicesCount, GLuint vao, GLuint vbo, GLuint ebo)
	: m_indiciesCount{ indicesCount },  m_vao { vao }, m_vbo{ vbo }, m_ebo{ ebo }
{

}

void Entity::render()
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glDrawArrays(GL_TRIANGLES, 0, m_indiciesCount);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Entity::cleanup()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
}