#ifndef LINE_H
#define LINE_H

#include <array>

#include "shape.h"
#include "matrix.h"

class Line: public Shape
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

    private:
        std::array<matrix*, 2> coordinates; // holds {start, end}
};

#endif