#include "Cell.hpp"
#include "Vertex.hpp"

#include <vector>

Cell::Cell()
	: m_walls{ 0b1111 }, m_searched{}, m_visited{ false }
{

}

void Cell::setLocation(unsigned int x, unsigned int z)
{
	m_x = x;
	m_z = z;
}

unsigned int Cell::getX() const
{
	return m_x;
}

unsigned int Cell::getZ() const
{
	return m_z;
}

void Cell::destroyWall(Direction direction)
{
	m_walls &= ~static_cast<unsigned char>(direction);
}

bool Cell::hasWall(Direction direction) const
{
	return m_walls & static_cast<unsigned char>(direction);
}

void Cell::markSearched(Direction direction)
{
	m_searched |= static_cast<unsigned char>(direction);
}

bool Cell::hasDirectionBeenSearched(Direction direction) const
{
	return m_searched & static_cast<unsigned char>(direction);
}

bool Cell::hasBeenSearched() const
{
	return m_searched == 0b1111;
}

void Cell::visit()
{
	m_visited = true;
}

bool Cell::hasBeenVisited() const
{
	return m_visited;
}