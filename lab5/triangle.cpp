#include "triangle.h"


Triangle::Triangle(int x0, int y0, int x1, int y1, int x2, int y2, unsigned int color): Polygon(color)
{
    Polygon::add_vertex(x0, y0);
    Polygon::add_vertex(x1, y1);
    Polygon::add_vertex(x2, y2);
}

std::shared_ptr<Shape> Triangle::clone() const
{
    return std::make_shared<Triangle>(*this);
}

/**
 * @brief IO Formatting
 * 
 * Files will be read from input streams and written to output streams in the
 * same format as Polygon but the type specified of the first line of the input:
 * 
 * Triangle: Polygon
 * <rest of polygon info>
 */

void Triangle::out(std::ostream& os) const
{
    os << "Triangle: ";
    Polygon::out(os);
}

std::ostream& operator<<(std::ostream& os, const Triangle& rhs)
{
    rhs.out(os);
    return os;
}

void Triangle::in(std::istream& is)
{
    // TODO
}