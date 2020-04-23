#ifndef IMAGE_H
#define IMAGE_H

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

    private:
        std::vector<Shape*> shapes;
};

#endif