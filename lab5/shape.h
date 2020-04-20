#ifndef SHAPE_H
#define SHAPE_H

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

    private:
        unsigned int color; // 32 or 64 bit integer to store hex color
};

#endif