#ifndef LINE_H
#define LINE_H

#include <memory>
#include <array>

#include "polygon.h"
#include "matrix.h"

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
         * @brief Print line properties to the output stream.
         * 
         * See definition for output format
         * 
         * @param os - Output Stream reference (std::ostream&)
         */
        void out(std::ostream& os);


        /**
         * @brief Construct a Line object from input stream
         * 
         * See definition for input format
         * 
         * @param is 
         */
        void in(std::istream& is);

    private:
};

#endif