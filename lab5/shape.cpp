#include "shape.h"
#include "line.h"
#include "triangle.h"

#include <string>
#include <sstream>

Shape::Shape(unsigned int color): color(color) {/*nothing else to do*/}

Shape::Shape(const Shape& from): color(from.color) {/*nothing else to do*/}

Shape::~Shape() {/*nothing to do*/}

/**
 * @brief Sets color of this to rhs
 * 
 * Leaves rest of the assignment process to derived class
 * 
 * @param rhs 
 * @return Shape& 
 */
Shape& Shape::operator=(const Shape& rhs)
{
    if (this != &rhs)
        color = rhs.color;       
    return *this;
}

/**
 * @brief Sets the color of the shape
 * 
 * Leaves rest of the assignment process to derived class
 * 
 * @param gc - GraphicsContext to draw in
 * @return Shape& - reference to this to allow chaining
 */
Shape& Shape::draw(GraphicsContext* gc)
{
    gc->setColor(this->color);
    return *this;
}

/**
 * @brief Puts this->color into os
 * 
 * @param os output stream that color is put into
 */
void Shape::out(std::ostream& os)
{
    os << color;
}

/**
 * @brief Populates a vector with appropriate shape objects
 * 
 * WARNING: Creates child objects from base. We probably shouldn't do that
 * 
 * https://cboard.cprogramming.com/cplusplus-programming/160713-reading-file-polymorphism.html
 * 
 * @param is 
 * @return std::istream& 
 */
void Shape::in(std::istream& in, std::vector<Shape*>& shapes)
{
    std::string line;
    while (getline(in, line))
    {
        std::stringstream ss(line);
        std::string type;
        if (ss >> type)
        {
            Shape* shape = nullptr;
            if (type == "Line")
            {
                shape = new Line(0,0,0,0,0);
            }
            else if (type == "Triangle")
            {
                shape = new Triangle(0,0,0,0,0,0,0);
            }
            else
            {
                // TODO handle an input error?
            }

            if (shape)
            {
                ss >> *shape;
                shapes.push_back(shape);
            }
        }
    }
}

std::istream& operator>>(std::istream& in, Shape& shape)
{
    shape.in(in);
    return in;
}