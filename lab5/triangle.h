#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <array>

#include "shape.h"
#include "matrix.h"

class Triangle: public Shape
{
    public:
        /**
         * @brief Construct a new Triangle object
         * 
         * @param x0 - starting x 
         * @param y0 - starting y
         * @param x1 - middle x
         * @param y1 - middle y
         * @param x2 - ending x
         * @param y2 - ending y
         * @param color - color of the Triangle
         */
        Triangle(int x0, int y0, int x1, int y1, int x2, int y2, unsigned int color);

        /**
         * @brief Copy construct a new Triangle object from another Triangle
         * 
         * @param from - Triangle to copy 
         */
        Triangle(const Triangle& from);

        /**
         * @brief Destroy the Triangle object
         * 
         */
        ~Triangle();

        /**
         * @brief Draw this Triangle in provided Graphics context.
         * 
         * @param gc - GraphicsContext to draw in
         * @return Shape& - reference to this to allow chaining
         */
        Triangle& draw(GraphicsContext* gc);

        /**
         * @brief Copy this Triangle object and return a Shape pointer to it
         * 
         * @return Shape* - pointer containing clone of this
         */
        Shape* clone();

        /**
         * @brief Create a new Triangle just like rhs. 
         * 
         * @param rhs - Triangle which properties are copied
         * @return Shape& - reference to this to allow chaining
         */
        Triangle& operator=(const Shape& rhs);

        /**
         * @brief Print Triangle properties to the output stream.
         * 
         * See definition for output format
         * 
         * @param os - Output Stream reference (std::ostream&)
         */
        void out(std::ostream& os);

        /**
         * @brief Construct a Triangle object from input stream
         * 
         * See definition for input format
         * 
         * @param is 
         */
        void in(std::istream& is);

    private:
        std::array<matrix*, 3> coordinates; // holds {start, middle, end}
};

#endif