#include "line.h"

Line::Line(int x0, int y0, int x1, int y1, unsigned int color): Shape(color)
{
    // TODO
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

Line& Line::draw(GraphicsContext& gc)
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