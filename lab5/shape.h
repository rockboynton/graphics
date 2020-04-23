#ifndef SHAPE_H
#define SHAPE_H

#include <iostream> // for std::ostream
#include <vector>

#include "gcontext.h"

/**
 * @brief Abstract shape base class
 * 
 */
class Shape
{
    public:
        /**
         * @brief Construct a new Shape object.
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
         * @brief Destroy the Shape object.
         * 
         * Not needed for base Shape, but called when children are destructed
         * 
         */
        virtual ~Shape();


        /**
         * @brief Draw shape in Graphics context.
         * 
         * Should not be called directly, instead as part of a concrete child class.
         * 
         * @param gc - GraphicsContext to draw in
         * @return Shape& - reference to this to allow chaining
         */
        virtual Shape& draw(GraphicsContext* gc); // ? Should this be protected?

        /**
         * @brief Print shape properties to the output stream.
         * 
         * Should not be called directly, instead as part of a concrete child class.
         * 
         * @param os - Output Stream reference (std::ostream&)
         */
        virtual void out(std::ostream& os);


        /**
         * @brief Construct a Shape object from input stream
         * 
         * Pure virtual function must be implemented by derived class.
         * 
         * @param is 
         */
        virtual void in(std::istream& is) = 0;

        /**
         * @brief Read shape properties from an input stream.
         * 
         * Designed to be be used to read from a text file and construct shapes
         * from it. This depends on concrete implementations/children of Shape
         * implementing in().
         * 
         * See definition for input format
         * 
         * @param is - Input Stream reference (std::ostream&)
         * @param shapes - vector of Shape* to populate
         */
        static void in(std::istream& is, std::vector<Shape*> shapes);

        virtual Shape* clone() = 0;

    protected:
        /**
         * @brief Create a new shape just like rhs. 
         * 
         * @param rhs - shape which properties are copied
         * @return Shape& - reference to this to allow chaining
         */
        virtual Shape& operator=(const Shape& rhs);
        
        unsigned int color; // 32 or 64 bit integer to store hex color
    private:
};

#endif