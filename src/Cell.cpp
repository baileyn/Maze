#include "Cell.hpp"

float Cell::WIDTH = 2.45f;
float Cell::HEIGHT = 2.45f;

Cell::Cell(Type type, unsigned int x, unsigned int y)
    : m_type{type}, m_x{x}, m_y{y}, m_directions{0b1111}, m_parent{nullptr}
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
