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

	bool hasWall(Direction direction) const;

private:
	unsigned int m_walls;
};

#endif // CELL_HPP