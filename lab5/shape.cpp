#include "shape.h"

Shape::Shape(unsigned int color): color(color)
{
    // nothing else to do
}

Shape::Shape(const Shape& from) 
{
    // TODO
}

Shape::~Shape() {}

/**
 * @brief Sets the color of the shape
 * 
 * This function expects to be called inside of children implementations
 * 
 * @param gc - GraphicsContext to draw in
 * @return Shape& - reference to this to allow chaining
 */
Shape& Shape::draw(GraphicsContext& gc)
{
    gc.setColor(this->color);
    return *this;
}