#ifndef SHAPE_H
#define SHAPE_H

#include <iostream> // for std::ostream

#include "gcontext.h"

/**
 * @brief Abstract shape base class
 * 
 */
class Shape
{
    public:
        /**
         * @brief Construct a new Shape object
         * 
         * No default constructor provided
         * 
         * @param color - color of the shape as a hex code
         */
        Shape(unsigned int color);

        /**
         * @brief Copy construct a new Shape object from another Shape
         * 
         * @param from - shape to copy 
         */
        Shape(const Shape& from);

        /**
         * @brief Destroy the Shape object
         * 
         * Not needed for base Shape, but called when children are destructed
         * 
         */
        virtual ~Shape();

        /**
         * @brief Create a new shape just like rhs. 
         * 
         * This is a pure virtual function. It should/can never be called by users.
         * 
         * @param rhs - shape which properties are copied
         * @return Shape& - reference to this to allow chaining
         */
        virtual Shape& operator=(const Shape& rhs) = 0;

        /**
         * @brief Draw shape in Graphics context
         * 
         * Should not be called directly, instead as part of a concrete child class.
         * 
         * @param gc - GraphicsContext to draw in
         * @return Shape& - reference to this to allow chaining
         */
        virtual Shape& draw(GraphicsContext& gc); // ? Should this be protected?

        /**
         * @brief Print shape properties to the output stream
         * 
         * Should not be called directly, instead as part of a concrete child class.
         * 
         * @param os - Output Stream reference (std::ostream&)
         * @return std::ostream& - reference to os to allow chaining
         */
        virtual std::ostream& out(std::ostream& os);

    private:
        unsigned int color; // 32 or 64 bit integer to store hex color
};

#endif