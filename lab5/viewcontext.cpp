#include "viewcontext.h"

std::unique_ptr<matrix> ViewContext::get_device_coords(matrix* model_coords) const
{
    // TODO
    return std::make_unique<matrix>(m2d);
}

std::unique_ptr<matrix> ViewContext::get_model_coords(matrix* device_coords) const
{
    // TODO
    return std::make_unique<matrix>(d2m);
}

void ViewContext::set_device_coords(matrix* model_coords)
{
    // TODO
}

void ViewContext::set_model_coords(matrix* device_coords)
{
    // TODO
}