#ifndef SHAPE_H
#define SHAPE_H

#include <iostream> // for std::ostream, std::istream
#include <vector>
#include <memory> // for shared_ptr

#include "gcontext.h"

/**
 * @brief Abstract shape base class
 * 
 */
class Shape
{
    public:
        /* No default constructor provided */

        /**
         * @brief Construct a new Shape object.
         * 
         * @param color - color of the shape as a hex code
         */
        Shape(unsigned int color);

        /**
         * @brief Copy construct a new Shape object from another Shape
         * 
         * @param from - shape to copy 
         */
        Shape(const Shape& from) = default; // color is copied by default

        /**
         * @brief Destroy the Shape object.
         * 
         * Not needed for base Shape, but called when children are destructed
         */
        virtual ~Shape() = default; // color is deleted off the stack by default

        /**
         * @brief Draw shape in Graphics context.
         * 
         * Should not be called directly, instead as part of a concrete child class.
         * 
         * @param gc - GraphicsContext to draw in
         * @return Shape& - reference to this to allow chaining
         */
        virtual const Shape& draw(GraphicsContext* gc) const;

        /**
         * @brief Print shape properties to the output stream.
         * 
         * Should not be called directly, instead as part of a concrete child class.
         * 
         * See definition for output format
         * 
         * @param os - Output Stream reference (std::ostream&)
         */
        virtual void out(std::ostream& os) const;

        /**
         * @brief Read shape properties from an input stream.
         * 
         * Designed to be be used to read from a text file and construct shapes
         * from it. This depends on concrete implementations/children of Shape
         * implementing in().
         * 
         * See definition for input format
         * 
         * @param in - Input Stream reference (std::ostream&)
         */
        virtual void in(std::istream& in);

        /**
         * @brief Used to create a shape (smart) pointer from a child object
         * 
         * @return std::shared_ptr<Shape> 
         */
        virtual std::shared_ptr<Shape> clone() const = 0;

    protected:
        /**
         * @brief Create a new shape just like rhs. 
         * 
         * @param rhs - shape which properties are copied
         * @return Shape& - reference to this to allow chaining
         */
        virtual Shape& operator=(const Shape& rhs) = default;
        
    private:
        unsigned int color; // 32 or 64 bit integer to store hex color
};

std::ostream& operator<<(std::ostream& os, const Shape& rhs);
std::istream& operator>>(std::istream& in, Shape& shape);

#endif