#include "polygon.h"


/**
 * @brief Construct a new Polygon object
 * 
 * Construct the start and end coordinates of this line and set the color
 * See matrix::coordinate
 */
Polygon::Polygon(unsigned int color): Shape(color){}

void Polygon::add_vertex(int x, int y) 
{
    coordinates.push_back(matrix::coordinate(x, y));
}

Polygon& Polygon::draw(GraphicsContext* gc)
{
    auto n = coordinates.size();
    for (auto i = 0U; i < n; ++i) {
        int x0 = coordinates[i][0][0];
        int y0 = coordinates[i][1][0];
        int x1 = coordinates[(i+1) % n][0][0];
        int y1 = coordinates[(i+1) % n][1][0];
        gc->drawLine(x0, y0, x1, y1);
    }
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