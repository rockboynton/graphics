#ifndef IMAGE_H
#define IMAGE_H

#include "shape.h"
#include "viewcontext.h"


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
         * @brief Add several shapes to this image
         * 
         * @param shapes - shapes to be added
         * @return Image& - reference to this, to allow chaining
         */
        void add(std::initializer_list<Shape*> shape_list);

        /**
         * @brief Add a shape to this image
         * 
         * @param shape - shape to be added
         * @return Image& - reference to this, to allow chaining
         */
        Image& add(Shape* shape);

        Image& add(std::shared_ptr<Shape> shape);

        /**
         * @brief Draws all shapes in this image
         * 
         * @param gc - GraphicsContext to draw in
         * @param vc - The view context to use to convert from model->device coords
         */
        void draw(GraphicsContext* gc, ViewContext* vc) const;

        /**
         * @brief Read image properties from an input stream
         * 
         * Designed to be be used to read shapes from a text file.
         * It will add all shapes read in to this image.
         * 
         * See definition for input format
         * 
         * Note: Incorrect input will lead to undefined behavior
         * 
         * @param is - Input Stream reference (std::istream&)
         */
        void in(std::istream& in);

        /**
         * @brief Print image properties to the output stream
         * 
         * Prints all shapes in this image
         * 
         * See definition for output format
         * 
         * @param os - Output Stream reference (std::ostream&)
         */
        void out(std::ostream& os) const;

        /**
         * @brief Remove all the shapes from this image
         * 
         */
        void erase();

    private:
        // using a vector because order matters (overlapping shapes will have
        // last shape's color on top) and fast iteration is important for drawing
        std::vector<std::shared_ptr<Shape>> shapes;
};

std::ostream& operator<<(std::ostream& os, const Image& rhs);
std::istream& operator>>(std::istream& in, Image& rhs);

#endif