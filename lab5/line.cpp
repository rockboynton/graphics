#include "line.h"


/**
 * @brief Construct a new Line object
 * 
 * Construct the start and end coordinates of this line and set the color
 * See matrix::coordinate
 */
Line::Line(int x0, int y0, int x1, int y1, unsigned int color): Polygon(color)
{
    Polygon::add_vertex(x0, y0);
    Polygon::add_vertex(x1, y1);
}

std::unique_ptr<Shape> Line::clone() const
{
    return std::make_unique<Line>(*this);
}

void Line::out(std::ostream& os)
{
    // TODO
}

void Line::in(std::istream& is)
{
    // TODO
}