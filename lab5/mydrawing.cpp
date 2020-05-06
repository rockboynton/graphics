#include "mydrawing.h"
#include "gcontext.h"

// Constructor
MyDrawing::MyDrawing()
{
    dragging = false;
    x0 = x1 = y0 = y1 = 0;
    return;
}

void MyDrawing::paint(GraphicsContext* gc)
{
    // for fun, let's draw a "fixed" shape in the middle of the screen // it will only show up after an exposure
    int middlex = gc->getWindowWidth()/2; int middley = gc->getWindowHeight()/2;
    gc->setColor(GraphicsContext::MAGENTA);
    for (int yi=middley-50;yi<=middley+50;yi++)
    {
        gc->drawLine(middlex-50,yi,middlex+50,yi);
    }

    gc->setColor(GraphicsContext::GREEN);
    // redraw the line if requested
    gc->drawLine(x0,y0,x1,y1);

    return;
}

void MyDrawing::mouseButtonDown(GraphicsContext* gc, unsigned int button, int x, int y) {
    // mouse button pushed down
    // - clear context
    // - set origin of new line // - set XOR mode for rubber-banding
    // - draw new line in XOR mode. Note, at this point, the line is
    // degenerate (0 length), but need to do it for consistency
    x0 = x1 = x;
    y0 = y1 = y;
    gc->setMode(GraphicsContext::MODE_XOR);
    gc->drawLine(x0,y0,x1,y1);
    dragging = true;
    return;
}

void MyDrawing::mouseButtonUp(GraphicsContext* gc, unsigned int button, int x, int y)
{
    if(dragging)
    {
        // undraw old line
        gc->drawLine(x0,y0,x1,y1);
        // just in x and y here do not match x and y of last mouse move
        x1 = x;
        y1 = y;
        // go back to COPY mode
        gc->setMode(GraphicsContext::MODE_NORMAL);
        // new line drawn in copy mode
        gc->drawLine(x0,y0,x1,y1);
        // clear flag
        dragging = false;
    }
    return;
}

void MyDrawing::mouseMove(GraphicsContext* gc, int x, int y)
{
    if(dragging)
    {
        // mouse moved - "undraw" old line, then re-draw in new position
        // will already be in XOR mode if dragging
        // old line undrawn
        gc->drawLine(x0,y0,x1,y1);
        // update
        x1 = x;
        y1 = y;
        // new line drawn
        gc->drawLine(x0,y0,x1,y1);
    }
    return;
}