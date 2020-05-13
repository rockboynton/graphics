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
        std::unique_ptr<matrix> get_device_coords(matrix* model_coords) const;
        std::unique_ptr<matrix> get_model_coords(matrix* device_coords) const;

        void set_device_coords(matrix* model_coords);
        void set_model_coords(matrix* device_coords);
};

#endif