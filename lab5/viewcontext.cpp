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
    d2m = flip * translation;
}

std::unique_ptr<matrix> ViewContext::get_device_coords(const std::unique_ptr<matrix> model_coords) const
{
    return std::make_unique<matrix>(m2d * (*model_coords));
}

std::unique_ptr<matrix> ViewContext::get_model_coords(const std::unique_ptr<matrix> device_coords) const
{
    return std::make_unique<matrix>(d2m * (*device_coords));
}

void ViewContext::translate(int dx, int dy)
{
    // update model->device
    m2d = m2d * matrix::translation(dx, dy);

    // update device->model
    d2m = matrix::translation(-dx, -dy) * d2m;
}

void ViewContext::scale(double scale_x, double scale_y)
{
    // update model->device
    m2d = m2d * matrix::scale(scale_x, scale_y);

    // update device->model
    d2m = matrix::scale(-scale_x, -scale_y) * d2m;
}