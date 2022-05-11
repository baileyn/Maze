#include "Cell.hpp"
#include "Vertex.hpp"

#include <vector>

Cell::Cell()
	: m_walls{ 0b1111 }
{

}

bool Cell::hasWall(Direction direction) const
{
	return m_walls & static_cast<unsigned char>(direction);
}