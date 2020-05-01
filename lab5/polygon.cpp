#include "polygon.h"

#include <iterator> // for ostream_iterator


/**
 * @brief Construct a new Polygon object
 */
Polygon::Polygon(unsigned int color): Shape(color){}

void Polygon::add_vertex(int x, int y) 
{
    coordinates.push_back(matrix::coordinate(x, y));
}

/**
 * @brief Draws the polygon
 * 
 * Draws a line from each vertex to the next in order that they were added
 * Connects final vertex to the first vertex.
 * 
 * In the case of a line, it draws it twice (overlap)
 */
Polygon& Polygon::draw(GraphicsContext* gc)
{
    Shape::draw(gc);
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

std::unique_ptr<Shape> Polygon::clone() const
{
    return std::make_unique<Polygon>(*this);
}

void Polygon::out(std::ostream& os) const
{
    os << "Polygon" << '\n';
    Shape::out(os);
    std::copy(coordinates.begin(), coordinates.end(), std::ostream_iterator<matrix>(os, ""));
    os << "end" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Polygon& rhs)
{
    rhs.out(os);
    return os;
}

void Polygon::in(std::istream& is)
{
    // TODO
}