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

    private:
        std::vector<std::unique_ptr<Shape>> shapes;
};

#endif