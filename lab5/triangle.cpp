#include "triangle.h"


Triangle::Triangle(int x0, int y0, int x1, int y1, int x2, int y2, unsigned int color): Shape(color)
{
    // TODO
}

Triangle::Triangle(const Triangle& from): Shape(from.color)
{
    // TODO
}

Triangle::~Triangle()
{
    // TODO
}

Triangle& Triangle::draw(GraphicsContext* gc)
{
    // TODO
    return *this;
}

Shape* Triangle::clone()
{
    // TODO
    return this;
}

Triangle& Triangle::operator=(const Shape& rhs)
{
    // TODO
    return *this;
}

void Triangle::out(std::ostream& os)
{
    // TODO
}

void Triangle::in(std::istream& is)
{
    // TODO
}