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
         * @param rhs 
         * @return Shape& 
         */
        virtual Shape& operator=(const Shape& rhs) = 0;

    private:
        unsigned int color; // 32 or 64 bit integer to store hex color
};

#endif