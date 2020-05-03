#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "polygon.h"

class Triangle: public Polygon
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
         * @brief Copy this triangle object and return a Shape pointer to it
         * 
         * @return Std::unique_ptr<Shape> - smart pointer containing clone of this
         */
        virtual std::shared_ptr<Shape> clone() const;

        /**
         * @brief Print Triangle properties to the output stream.
         * 
         * See definition for output format
         * 
         * @param os - Output Stream reference (std::ostream&)
         */
        void out(std::ostream& os) const;

        /**
         * @brief Construct a Triangle object from input stream
         * 
         * See definition for input format
         * 
         * @param is 
         */
        void in(std::istream& is);

    private:
        using Polygon::add_vertex; // not allowed to add vertex to a triangle
};

std::ostream& operator<<(std::ostream& os, const Triangle& rhs);

#endif