#include "shape.h"
#include "line.h"
#include "triangle.h"
#include "polygon.h"

#include <string>
#include <sstream>

Shape::Shape(unsigned int color): color(color) {/*nothing else to do*/}

/**
 * @brief Sets the color of the shape
 * 
 * Leaves rest of the assignment process to derived class
 * 
 */
const Shape& Shape::draw(GraphicsContext* gc, ViewContext* vc) const
{
    gc->setColor(this->color);
    return *this;
}

/**
 * @brief Puts this->color into os
 */
void Shape::out(std::ostream& os) const
{
    os << color << '\n';
    os << "endShape" << '\n';
}

std::ostream& operator<<(std::ostream& os, const Shape& rhs)
{
    rhs.out(os);
    return os;
}

/**
 * @brief Reads a color and puts it in this->color
 */
void Shape::in(std::istream& in)
{
    std::string ignore; // to ignore endShape
    in >> color >> ignore;
}

std::istream& operator>>(std::istream& in, Shape& shape)
{
    shape.in(in);
    return in;
}