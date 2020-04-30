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

void Image::in(std::istream& is)
{
    // TODO
}

void Image::out(std::ostream& os)
{
    // TODO
}

void Image::erase()
{
    // TODO
}