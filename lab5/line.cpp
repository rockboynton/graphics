#include "line.h"

Line::Line(int x0, int y0, int x1, int y1, unsigned int color): Shape(color)
{
    // TODO
}

Line::~Line()
{
    // TODO
}

Shape& Line::draw(GraphicsContext& gc)
{
    // TODO
    return *this;
}

Shape* Line::clone()
{
    // TODO
    return this;
}