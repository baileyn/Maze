#ifndef CELL_HPP
#define CELL_HPP
#pragma once

class Cell
{
public:
    static float WIDTH;
    static float HEIGHT;

    enum class Type {
        Wall,
        Room
    };

    Cell(Type type, unsigned int x, unsigned int y);

    unsigned int getX() const;
    unsigned int getY() const;

    Cell* getParent();
    void setParent(Cell* parent);

private:
    Type m_type;
    unsigned int m_x;
    unsigned int m_y;
    unsigned int m_directions;
    Cell* m_parent;
};

#endif // CELL_HPP