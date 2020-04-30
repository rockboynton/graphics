#include "triangle.h"


Triangle::Triangle(int x0, int y0, int x1, int y1, int x2, int y2, unsigned int color): Polygon(color)
{
    Polygon::add_vertex(x0, y0);
    Polygon::add_vertex(x1, y1);
    Polygon::add_vertex(x2, y2);
}

void Triangle::out(std::ostream& os)
{
    // TODO
}

void Triangle::in(std::istream& is)
{
    // TODO
}