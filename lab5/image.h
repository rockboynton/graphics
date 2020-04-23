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

    private:
        std::vector<Shape*> shapes;
};

#endif