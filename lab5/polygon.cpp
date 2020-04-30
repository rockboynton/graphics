#include "polygon.h"


/**
 * @brief Construct a new Polygon object
 * 
 * Construct the start and end coordinates of this line and set the color
 * See matrix::coordinate
 */
Polygon::Polygon(unsigned int color): Shape(color)
{
    
}

void Polygon::add_vertex(int x, int y) 
{
    coordinates.push_back(matrix::coordinate(x, y));
}

Polygon::Polygon(const Polygon& from): Shape(from.color)
{
    coordinates = from.coordinates;
}

void swap(Polygon& first, Polygon& second)
{
    using std::swap;
    swap(first.coordinates, second.coordinates);
}

Polygon& Polygon::operator=(Polygon rhs)
{
    swap(*this, rhs);
    return *this;
}

Polygon::~Polygon()
{
}

Polygon& Polygon::draw(GraphicsContext* gc)
{
    // TODO
    return *this;
}

Shape* Polygon::clone()
{
    // TODO
    return this;
}

void Polygon::out(std::ostream& os)
{
    // TODO
}

void Polygon::in(std::istream& is)
{
    // TODO
}