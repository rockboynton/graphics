#include "image.h"

Image& Image::add(Shape* shape)
{
    shapes.insert(shape->clone());
    return *this;
}

void Image::add(std::initializer_list<Shape*> shapes)
{
    for (auto& shape : shapes) {
        (this->shapes).insert(shape->clone());
    }
}

void Image::draw(GraphicsContext* gc)
{
    for (auto& shape : shapes) {
        shape->draw(gc);
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

void Image::in(std::istream& is)
{
    // TODO
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

void Image::erase()
{
    shapes.clear();
}