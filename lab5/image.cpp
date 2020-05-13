#include "image.h"

#include "line.h"
#include "triangle.h"
#include "polygon.h"

/**
 * @brief Adds a shape by calling shape's clone() method
 * 
 * Clone method will handle creating a Shape pointer from 
 * whatever derived object the shape is
 * 
 * @param shape - the shape to add
 * @return Image& - reference to this to allow chaining
 */
Image& Image::add(Shape* shape)
{
    shapes.emplace_back(shape->clone());
    return *this;
}

Image& Image::add(std::shared_ptr<Shape> shape)
{
    shapes.emplace_back(shape->clone());
    return *this;
}

void Image::add(std::initializer_list<Shape*> shape_list)
{
    for (auto& shape : shape_list) {
        shapes.emplace_back(shape->clone());
    }
}

/**
 * @brief Iterates over all shapes in this imagedraws them
 * 
 * Calls the shape's draw() method
 * 
 * @param gc 
 */
void Image::draw(GraphicsContext* gc, ViewContext* vc) const
{
    for (auto& shape : shapes) {
        shape->draw(gc, vc);
    }
}

/**
 * @brief IO Formatting
 * 
 * Files will be read from input streams and written to output streams in the
 * following format:
 * 
 * Image:
 * <shape 1 output>
 * <shape 2 output>
 * .
 * .
 * .
 * <shape n output>
 * endImage
 * 
 */

void Image::in(std::istream& in)
{
    std::string type;
    in >> type; // Ignore header
    while (in >> type)
    {
        std::cout << type << std::endl;
        std::shared_ptr<Shape> shape;
        if (type == "Line:")
        {
            shape = std::make_shared<Line>(0,0,0,0,0);
        }
        else if (type == "Triangle:")
        {
            shape = std::make_shared<Triangle>(0,0,0,0,0,0,0);
        }
        else if (type == "Polygon")
        {
            shape = std::make_shared<Polygon>(0);
        } else {
            break; // done reading shapes
        }
        in >> *shape;
        shapes.emplace_back(shape);
    }
}

void Image::out(std::ostream& os) const
{
    os << "Image: " << '\n';
    for (auto& shape : shapes) {
        os << *shape;
    }
    os << "endImage" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Image& rhs)
{
    rhs.out(os);
    return os;
}

std::istream& operator>>(std::istream& in, Image& rhs)
{
    rhs.in(in);
    return in;
}

void Image::erase()
{
    shapes.clear();
}