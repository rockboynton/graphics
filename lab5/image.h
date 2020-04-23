#ifndef IMAGE_H
#define IMAGE_H

#include <memory>
#include <vector>

#include "shape.h"

class Image
{
    public:
        /**
         * @brief Construct a new Image object
         * 
         */
        Image();

        /**
         * @brief Construct a new Image object from another image
         * 
         * @param from - Image to copy
         */
        Image(const Image& from);

        /**
         * @brief Destroy the Image object
         * 
         */
        ~Image();

        /**
         * @brief Add a shape to this image
         * 
         * @param shape - shape to be added
         * @return Image& - reference to this, to allow chaining
         */
        Image& add(Shape* shape);

    private:
        std::vector<std::unique_ptr<Shape>> shapes;
};

#endif