#ifndef IMAGE_H
#define IMAGE_H

#include <memory>
#include <set>

#include "shape.h"

class Image
{
    public:
        /**
         * @brief Construct a new Image object
         * 
         */
        Image() = default;

        /**
         * @brief Construct a new Image object from another image
         * 
         * Performs deep copy by default
         * 
         * @param from - Image to copy
         */
        Image(const Image& from) = default;

        /**
         * @brief Destroy the Image object
         * 
         */
        ~Image() = default;

        /**
         * @brief Assigns an image to contain the same shapes as another image
         * 
         * @param rhs - Image to assign
         * @return Image& - reference to this to allow chaining
         */
        Image& operator=(const Image& rhs) = default;

        /**
         * @brief Add a shape to this image
         * 
         * @param shape - shape to be added
         * @return Image& - reference to this, to allow chaining
         */
        void add(std::initializer_list<Shape*> shapes);

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

        /**
         * @brief Remove all the shapes from this image
         * 
         */
        void erase();

    private:
        std::set<std::unique_ptr<Shape>> shapes;
};

#endif