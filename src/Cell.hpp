#ifndef CELL_HPP
#define CELL_HPP
#pragma once

#include <glad/glad.h>

class Cell
{
public:
	/**
	 * @brief an enumeration to represent a Direction.
	 */
	enum class Direction : unsigned char {
		FRONT = 0b0001, 
		BACK  = 0b0010, 
		LEFT  = 0b0100, 
		RIGHT = 0b1000
	};

	/**
	 * @brief the width of a Cell in OpenGL units.
	 */
    static constexpr float WIDTH = 10.0f;

	/**
	 * @brief the height of a Cell in OpenGL units.
	 * 
	 */
    static constexpr float HEIGHT = 2.45f;

	/**
	 * @brief constructs a new Cell that's located at 0,0
	 */
	Cell();

	/**
	 * @brief sets the current location of this Cell.
	 * 
	 * @param x the position of this Cell on the x axis.
	 * @param z the position of this Cell on the z axis.
	 */
	void setLocation(unsigned int x, unsigned int z);

	/**
	 * @brief returns the position of this Cell on the x axis.
	 * 
	 * @return unsigned int the position of this Cell on the x axis.
	 */
	unsigned int getX() const;

	/**
	 * @brief returns the position of this Cell on the z axis.
	 * 
	 * @return unsigned int the position of this Cell on the z axis.
	 */
	unsigned int getZ() const;

	/**
	 * @brief marks the wall in the specified direction to not be rendered.
	 * 
	 * @param direction the direction of the wall to destroy.
	 */
	void destroyWall(Direction direction);

	/**
	 * @brief determines whether or not this Cell has a wall in the specified direction.
	 * 
	 * @param direction the direction to look for a wall in.
	 * @return true if the wall exists.
	 * @return false if the wall doesn't exist.
	 */
	bool hasWall(Direction direction) const;
	
	/**
	 * @brief marks the specified Direction as being searched from this Cell.
	 * 
	 * @param direction the direction to mark.
	 */
	void markSearched(Direction direction);

	/**
	 * @brief determines if the specified direction has been searched from this Cell.
	 * 
	 * @param direction the direction to examine.
	 * @return true if the direction has been searched from this Cell.
	 * @return false if the direction hasn't been searched from this Cell.
	 */
	bool hasDirectionBeenSearched(Direction direction) const;

	/**
	 * @brief determines if every direction has been searched from this Cell.
	 * 
	 * @return true if every direction has been searched from this Cell.
	 * @return false if directions remain to be searched from this Cell.
	 */
	bool hasBeenSearched() const;

	/**
	 * @brief marks this Cell to denote it has been visited.
	 */
	void visit();

	/**
	 * @brief determines if this Cell has been visited.
	 * 
	 * @return true if this Cell has been visited.
	 * @return false if this Cell hasn't been visited.
	 */
	bool hasBeenVisited() const;

private:
	unsigned int m_x;
	unsigned int m_z;
	unsigned int m_walls;
	unsigned int m_searched;
	bool m_visited;
};

#endif // CELL_HPP