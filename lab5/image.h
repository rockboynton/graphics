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

        /**
         * @brief Draws all shapes in this image
         * 
         * @param gc - GraphicsContext to draw in
         */
        void draw(GraphicsContext* gc);

        /**
         * @brief Read shape properties from an input stream
         * 
         * Designed to be be used to read from a text file and construct shapes
         * from it. It will add all shapes read in to this image
         * 
         * See definition for input format
         * 
         * @param is - Input Stream reference (std::ostream&)
         */
        void in(std::istream& is);

    private:
        std::vector<std::unique_ptr<Shape>> shapes;
};

#endif