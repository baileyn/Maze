#include "Cell.hpp"
#include "Vertex.hpp"

#include <vector>

constexpr float HALF_WIDTH = Cell::WIDTH / 2;
constexpr float HALF_HEIGHT = Cell::HEIGHT / 2;

static std::vector<Vertex> VERTICES = {
	{ { 0, Cell::HEIGHT, 0 },{ 1, 0, 0 } }, // Front Top Left
	{ { 0, 0, 0 }, { 1, 0, 0 } }, // Front Bottom Left
	{ { Cell::WIDTH, Cell::HEIGHT, 0 }, { 1,0,0} }, // Front Top Right
	{ { Cell::WIDTH, 0, 0 }, { } }, // Front Bottom Right
};

static std::vector<GLuint> INDICIES = {
	0, 1, 2,
	2, 1, 3
};

Cell::Cell(Type type, unsigned int x, unsigned int y)
    : m_type{type}, m_x{x}, m_y{y}, m_directions{0b1111}, m_parent{nullptr},
	m_vao{}, m_vbo{}, m_ebo{}
{
}

unsigned int Cell::getX() const
{
    return m_x;
}

unsigned int Cell::getY() const
{
    return m_y;
}

Cell* Cell::getParent()
{
    return m_parent;
}

void Cell::setParent(Cell* parent)
{
    m_parent = parent;
}

void Cell::init()
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	glBindVertexArray(m_vao);
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDICIES.size() * sizeof(INDICIES[0]), INDICIES.data(), GL_STATIC_DRAW);
		
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, VERTICES.size() * sizeof(VERTICES[0]), VERTICES.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);

	}
	glBindVertexArray(0);
}

void Cell::render()
{

}
