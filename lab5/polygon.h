#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"
#include "matrix.h"
#include "viewcontext.h"


/**
 * @brief Class to represent a polygon object
 * 
 * A polygon is a sequence of vertices connected by lines, 
 * with the last vertex connecting to the first one.
 * 
 */
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
        Polygon(const Polygon& from) = default; 

        /**
         * @brief Create a new polygon just like rhs. 
         * 
         * @param rhs - polygon which properties are copied
         * @return Shape& - reference to this to allow chaining
         */
        virtual Polygon& operator=(const Polygon& rhs) = default;

        /**
         * @brief Destroy the Polygon object
         */
        virtual ~Polygon() = default;

        /**
         * @brief Draw this polygon in provided Graphics context.
         * 
         * @param gc - GraphicsContext to draw in
         * @return Shape& - reference to this to allow chaining
         */
        const Polygon& draw(GraphicsContext* gc, ViewContext* vc) const;

        /**
         * @brief Copy this polygon object and return a Shape pointer to it
         * 
         * @return Shape* - pointer containing clone of this
         */
        virtual std::shared_ptr<Shape> clone() const;

        /**
         * @brief Print polygon properties to the output stream.
         * 
         * See definition for output format
         * 
         * @param os - Output Stream reference (std::ostream&)
         */
        virtual void out(std::ostream& os) const;

        /**
         * @brief Construct this Polygon object from input stream
         * 
         * See definition for input format
         * 
         * @param is 
         */
        virtual void in(std::istream& is);

        /**
         * @brief Adds a vertext to this polygon
         * 
         * @param x 
         * @param y 
         */
        virtual void add_vertex(int x, int y);

    private:
        std::vector<matrix> coordinates; // holds {start, ..., end}
};

std::ostream& operator<<(std::ostream& os, const Polygon& rhs);
std::istream& operator>>(std::istream& in, Polygon& rhs);

#endif