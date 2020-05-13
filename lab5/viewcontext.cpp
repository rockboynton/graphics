#include "viewcontext.h"

ViewContext::ViewContext(int dx, int dy) : m2d(4, 4), d2m(4, 4)
{
    // make model->device
    matrix translation = matrix::translation(dx / 2, dy / 2);
    matrix flip = matrix::scale(1, -1);
    m2d = translation * flip;

    // make device->model
    translation = matrix::translation(-dx / 2, -dy / 2);
    flip = matrix::scale(1, -1);
    m2d = flip * translation;
}

std::unique_ptr<matrix> ViewContext::get_device_coords(const std::unique_ptr<matrix> model_coords) const
{
    // TODO
    return std::make_unique<matrix>(m2d);
}

std::unique_ptr<matrix> ViewContext::get_model_coords(const std::unique_ptr<matrix> device_coords) const
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