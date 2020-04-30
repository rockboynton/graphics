#ifndef POLYGON_H
#define POLYGON_H

#include <memory>
#include <array>

#include "shape.h"
#include "matrix.h"

class Polygon: public Shape
{
    public:
        /**
         * @brief Construct a new Polygon object
         * @param color - color of the polygon
         */
        Polygon(unsigned int color);

        /**
         * @brief Copy construct a new Polygon object from another Polygon
         * 
         * @param from - polygon to copy 
         */
        Polygon(const Polygon& from);

        friend void swap(Polygon& first, Polygon& second);

        /**
         * @brief Create a new polygon just like rhs. 
         * 
         * @param rhs - polygon which properties are copied
         * @return Shape& - reference to this to allow chaining
         */
        Polygon& operator=(Polygon rhs);

        /**
         * @brief Destroy the Polygon object
         * 
         */
        ~Polygon();

        /**
         * @brief Draw this polygon in provided Graphics context.
         * 
         * @param gc - GraphicsContext to draw in
         * @return Shape& - reference to this to allow chaining
         */
        Polygon& draw(GraphicsContext* gc);

        /**
         * @brief Copy this polygon object and return a Shape pointer to it
         * 
         * @return Shape* - pointer containing clone of this
         */
        Shape* clone();


        /**
         * @brief Print polygon properties to the output stream.
         * 
         * See definition for output format
         * 
         * @param os - Output Stream reference (std::ostream&)
         */
        void out(std::ostream& os);

        void add_vertex(int x, int y);

        /**
         * @brief Construct a Polygon object from input stream
         * 
         * See definition for input format
         * 
         * @param is 
         */
        void in(std::istream& is);

    protected:

    private:
        std::vector<matrix> coordinates; // holds {start, end}
};

#endif