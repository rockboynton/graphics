#include "line.h"


/**
 * @brief Construct a new Line object
 * 
 * Construct the start and end coordinates of this line and set the color
 * See matrix::coordinate
 */
Line::Line(int x0, int y0, int x1, int y1, unsigned int color): Shape(color)
{
    for (auto& coordinate : coordinates) {
        coordinate = new matrix(matrix::coordinate(x0, y0));
    }
}

Line::Line(const Line& from): Shape(from.color)
{
    coordinates = from.coordinates;
}

void swap(Line& first, Line& second)
{
    using std::swap;
    swap(first.coordinates, second.coordinates);
}

Line& Line::operator=(Line rhs)
{
    *this = rhs;
    swap(*this, rhs);
    return *this;
}

Line::~Line()
{
    for (auto& coordinate : coordinates) {
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