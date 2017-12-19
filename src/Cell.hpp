#ifndef CELL_HPP
#define CELL_HPP
#pragma once

#include <glad/glad.h>

class Cell
{
public:
	enum class Direction : unsigned char {
		FRONT = 0b0001, 
		BACK  = 0b0010, 
		LEFT  = 0b0100, 
		RIGHT = 0b1000
	};

    static constexpr float WIDTH = 10.0f;
    static constexpr float HEIGHT = 2.45f;

	Cell();

	void setLocation(unsigned int x, unsigned int z);
	unsigned int getX() const;
	unsigned int getZ() const;

	void destroyWall(Direction direction);
	bool hasWall(Direction direction) const;
	
	void markSearched(Direction direction);
	bool hasDirectionBeenSearched(Direction direction) const;
	bool hasBeenSearched() const;

	void visit();
	bool hasBeenVisited() const;

private:
	unsigned int m_x;
	unsigned int m_z;
	unsigned int m_walls;
	unsigned int m_searched;
	bool m_visited;
};

#endif // CELL_HPP