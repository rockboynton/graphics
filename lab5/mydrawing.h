#ifndef MYDRAWING_H
#define MYDRAWING_H

#include "drawbase.h"
#include "image.h"

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
        // We will only support one "remembered" line 
        // In an actual implementation, we would also have one of our "image" 
        // objects here to store all of our drawn shapes.
        int x0; int y0;
        int x1; int y1;
        bool dragging; // flag to know if we are dragging
        Image image;
        Shape* current_shape;

        static enum States {
            POINT, LINE, TRIANGLE_L1, TRIANGLE_L2, POLYGON_L1, POLYGON_LN, MAX_STATES
            } state;
            
        static enum Events {
            MOUSE_UP, MOUSE_DOWN, MOUSE_MOVE, MAX_EVENTS
            } event;
        
        // states are rows, events are columns
        void (*const state_table [MAX_STATES][MAX_EVENTS]) (void) = {
            {}, /* POINT */
            {}, 
            {}, 
            {}, 
            {}, 
            {}, 
        };
        unsigned int color;
};
#endif