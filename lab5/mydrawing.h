#ifndef MYDRAWING_H
#define MYDRAWING_H

#include "drawbase.h"
#include "image.h"
#include "line.h"
#include "triangle.h"

// forward reference
class GraphicsContext;

class MyDrawing : public DrawingBase
{
    public:
        MyDrawing(); 
        // we will override just these 
        virtual void paint(GraphicsContext* gc); 
        virtual void mouseButtonDown(GraphicsContext* gc, unsigned int button, int x, int y);
        virtual void mouseButtonUp(GraphicsContext* gc, unsigned int button, int x, int y); 
        virtual void mouseMove(GraphicsContext* gc, int x, int y); 
        virtual void keyDown(GraphicsContext* gc, unsigned int keycode);
        virtual void keyUp(GraphicsContext* gc, unsigned int keycode);
    private: 
        void save_image();
        void load_image(GraphicsContext* gc);
        std::vector<std::pair<int, int>> points; // at least 2 points in buffer
        bool dragging; // flag to know if we are dragging
        Image image;
        std::shared_ptr<Shape> current_shape;

        enum States {
            POINT, LINE, TRIANGLE_L1, TRIANGLE_L2, POLYGON_L1, POLYGON_LN
            } state;
            
        unsigned int color;

        void xor_line(GraphicsContext* gc, int x, int y);
        void copy_line(GraphicsContext* gc, int x, int y);
        void rubberband_poly(GraphicsContext* gc, int x, int y);

        /**
         * @brief Completes a polygon 
         * 
         * Draws line from last point to second to last point and
         * draws line from last point to first point.
         * 
         * @param gc 
         */
        void complete_polygon(GraphicsContext* gc, int x, int y);

        void print_points();
};
#endif