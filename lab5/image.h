#ifndef IMAGE_H
#define IMAGE_H

#include <memory>
#include <unordered_set>

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
         * @brief Read image properties from an input stream
         * 
         * Designed to be be used to read shapes from a text file.
         * It will add all shapes read in to this image.
         * 
         * See definition for input format
         * 
         * @param is - Input Stream reference (std::ostream&)
         */
        void in(std::istream& is);

        /**
         * @brief Print image properties to the output stream
         * 
         * Prints all shapes in this image
         * 
         * See definition for output format
         * 
         * @param os - Output Stream reference (std::ostream&)
         */
        void out(std::ostream& os);

    private:
        std::unordered_set<std::unique_ptr<Shape>> shapes;
};

#endif