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

std::shared_ptr<Shape> Line::clone() const
{
    return std::make_shared<Line>(*this);
}

/**
 * @brief IO Formatting
 * 
 * Files will be read from input streams and written to output streams in the
 * same format as Polygon but the type specified of the first line of the input:
 * 
 * Line: Polygon
 * <rest of polygon info>
 */

void Line::out(std::ostream& os) const
{
    os << "Line: ";
    Polygon::out(os);
}

std::ostream& operator<<(std::ostream& os, const Line& rhs)
{
    rhs.out(os);
    return os;
}

void Line::in(std::istream& is)
{
    Polygon::in(is);
}