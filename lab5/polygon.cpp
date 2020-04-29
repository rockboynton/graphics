#include "polygon.h"

const int Polygon::num_coordinates = 2;

/**
 * @brief Construct a new Polygon object
 * 
 * Construct the start and end coordinates of this line and set the color
 * See matrix::coordinate
 */
Polygon::Polygon(unsigned int sides, unsigned int color): Shape(color)
{
    for (auto& coordinate : coordinates) {
        coordinate = new matrix(matrix::coordinate(x0, y0));
    }
}

Polygon::Polygon(const Polygon& from): Shape(from.color)
{
    // coordinates = from.coordinates;
}

void swap(Polygon& first, Polygon& second)
{
    // using std::swap;
    // swap(first.coordinates, second.coordinates);
}

Polygon& Polygon::operator=(Polygon rhs)
{
    // *this = rhs;
    // swap(*this, rhs);
    return *this;
}

Polygon::~Polygon()
{
    // for (auto& coordinate : coordinates) {
    //     delete coordinate;
    // }
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