#ifndef CELL_HPP
#define CELL_HPP
#pragma once

#include <glad/glad.h>

class Cell
{
public:
    static constexpr float WIDTH = 2.45f;
    static constexpr float HEIGHT = 2.45f;

    enum class Type {
        Wall,
        Room
    };

    Cell(Type type, unsigned int x, unsigned int y);

    unsigned int getX() const;
    unsigned int getY() const;

    Cell* getParent();
    void setParent(Cell* parent);

	void init();
	void render();

private:
    Type m_type;
    unsigned int m_x;
    unsigned int m_y;
    unsigned int m_directions;
    Cell* m_parent;

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
};

#endif // CELL_HPP