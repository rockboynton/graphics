#include "polygon.h"

#include <iterator> // for ostream_iterator


/**
 * @brief Construct a new Polygon object
 */
Polygon::Polygon(unsigned int color): Shape(color){}

/**
 * @brief Adds a vertex as the last vertex of the polygon
 * 
 * @param x - x-coord
 * @param y - y-coord
 */
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
const Polygon& Polygon::draw(GraphicsContext* gc) const
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

std::shared_ptr<Shape> Polygon::clone() const
{
    return std::make_shared<Polygon>(*this);
}

/**
 * @brief IO Formatting
 * 
 * Files will be read from input streams and written to output streams in the
 * following format:
 * 
 * <type (if any): > Polygon <number of coordinates>
 * <vertex 1 x-coord>
 * <vertex 1 y-coord>
 * <vertex 1 z-coord>
 * <vertex 1 homogenous-coord>
 * .
 * .
 * .
 * <vertex n x-coord>
 * <vertex n y-coord>
 * <vertex n z-coord>
 * <vertex n homogenous-coord>
 * endPolygon
 * Color (hex code): <hex color>
 * endShape
 * 
 */

void Polygon::out(std::ostream& os) const
{
    os << "Polygon " << coordinates.size() << '\n';
    std::copy(coordinates.begin(), coordinates.end(), std::ostream_iterator<matrix>(os, ""));
    os << "endPolygon" << std::endl;
    Shape::out(os);
}

std::ostream& operator<<(std::ostream& os, const Polygon& rhs)
{
    rhs.out(os);
    return os;
}

void Polygon::in(std::istream& is)
{
    unsigned int size;
    is >> size;
    std::cout << size << "\n";
    coordinates.clear();
    for (auto i = 0U; i < size; ++i) {
        coordinates.emplace_back(matrix::COORDINATE_ROWS, matrix::COORDINATE_COLS);
        is >> coordinates[i];
    }
    std::string ignore;
    is >> ignore;
    Shape::in(is); 
}

std::istream& operator>>(std::istream& in, Polygon& rhs)
{
    rhs.in(in);
    return in;
}