#ifndef LINE_H
#define LINE_H

#include "polygon.h"

class Line: public Polygon
{
    public:
        /**
         * @brief Construct a new Line object
         * 
         * @param x0 - starting x 
         * @param y0 - starting y
         * @param x1 - ending x
         * @param y1 - ending y
         * @param color - color of the line
         */
        Line(int x0, int y0, int x1, int y1, unsigned int color);

        /**
         * @brief Copy this line object and return a Shape pointer to it
         * 
         * @return Std::unique_ptr<Shape> - smart pointer containing clone of this
         */
        std::shared_ptr<Shape> clone() const;

        /**
         * @brief Print line properties to the output stream.
         * 
         * See definition for output format
         * 
         * @param os - Output Stream reference (std::ostream&)
         */
        void out(std::ostream& os) const;

        /**
         * @brief Construct a Line object from input stream
         * 
         * See definition for input format
         * 
         * @param is 
         */
        void in(std::istream& is);

    private:
        using Polygon::add_vertex; // not allowed to add vertex to a line
};

std::ostream& operator<<(std::ostream& os, const Line& rhs);

#endif