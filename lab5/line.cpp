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
    int params[2][2] = {{x0, y0}, {x1, y1}};
    int point = 0;
    for (auto& coordinate : coordinates) {
        coordinate = std::make_unique<matrix>(matrix::COORDINATE_ROWS , matrix::COORDINATE_COLS);
        (*coordinate)[0][0] = params[point][0]; // x-coord
        (*coordinate)[1][0] = params[point++][1]; // y-coord
        (*coordinate)[2][0] = 0; // z-coord
        (*coordinate)[3][0] = 1; // homogenous-coord
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
    // TODO
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