#include "line.h"


/**
 * @brief Construct a new Line object
 * 
 * @param x0 
 * @param y0 
 * @param x1 
 * @param y1 
 * @param color 
 */
Line::Line(int x0, int y0, int x1, int y1, unsigned int color): Shape(color)
{
    for (auto& coordinate : coordinates) {
        coordinate = new matrix(matrix::coordinate(x0, y0));
    }
}

Line::Line(const Line& from): Shape(from.color)
{

}

Line& Line::operator=(const Shape& rhs)
{
    return *this;
}

Line::~Line()
{
    for (auto coordinate : coordinates) {
        delete coordinate;
    }
}

Line& Line::draw(GraphicsContext* gc)
{
    // TODO
    return *this;
}

Shape* Line::clone()
{
    // TODO
    return this;
}

void Line::out(std::ostream& os)
{
    // TODO
}

void Line::in(std::istream& is)
{
    // TODO
}