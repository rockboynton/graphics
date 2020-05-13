#ifndef VIEWCONTEXT_H
#define VIEWCONTEXT_H

#include "matrix.h"

#include <memory>

class ViewContext
{

    private:
        matrix m2d; // model -> device matrix
        matrix d2m; // device -> model matrix

    public:
        /**
         * @brief Construct a new View Context object
         * 
         * Sets the "model coordinates” origin to be in the center of the display
         * device with the Y-axis in normal Cartesian configuration. 
         * There should is intially no other rotation, translation, or scaling.
         * 
         * @param dx width of display
         * @param dy height of display
         */
        ViewContext(int dx, int dy);

        std::unique_ptr<matrix> get_device_coords(const std::unique_ptr<matrix> model_coords) const;
        std::unique_ptr<matrix> get_model_coords(const std::unique_ptr<matrix> device_coords) const;

        void set_device_coords(matrix* model_coords);
        void set_model_coords(matrix* device_coords);
};

#endif