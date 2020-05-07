#include "mydrawing.h"
#include "gcontext.h"

// Constructor
MyDrawing::MyDrawing()
{
    dragging = false;
    x0 = x1 = y0 = y1 = 0;

    // TODO print instructions

    return;
}

void MyDrawing::paint(GraphicsContext* gc)
{
    image.draw(gc);
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
    gc->setColor(color);
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
        gc->setColor(color);
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
        gc->setColor(color);
        gc->drawLine(x0,y0,x1,y1);
        // update
        x1 = x;
        y1 = y;
        // new line drawn
        gc->drawLine(x0,y0,x1,y1);
    }
    return;
}

void MyDrawing::keyDown(GraphicsContext* gc, unsigned int keycode)
{
    switch(keycode) {
        case 'x':
            image.erase();
            gc->clear();
            break;
        case 'p':
            state = POINT;
            break;
        case 'l':
            state = LINE;
            break;
        case 't': 
            state = TRIANGLE;
            break;
        case 'o':
            state = POLYGON;
            break;
        case 's':
            save_image();
            break;
        case 'd':
            load_image(gc);
            break;
        case '1':
            color = GraphicsContext::RED;
            break;
        case '2':
            color = GraphicsContext::YELLOW;
            break;
        case '3':
            color = GraphicsContext::GREEN;
            break;
        case '4':
            color = GraphicsContext::BLUE;
            break;
        case '5':
            color = GraphicsContext::CYAN;
            break;
        case '6':
            color = GraphicsContext::MAGENTA;
            break;
        case '7':
            color = GraphicsContext::BLACK;
            break;
        case '8':
            color = GraphicsContext::WHITE;
            break;
        case '9':
            color = GraphicsContext::GRAY;
            break;
        default:
            std::cout << keycode << " not recognized as a command" << std::endl;
            break;
    }
}

void MyDrawing::keyUp(GraphicsContext* gc, unsigned int keycode)
{
    
}

void MyDrawing::save_image()
{
    // TODO
}

void MyDrawing::load_image(GraphicsContext* gc)
{
    image.erase();
    gc->clear();
    // TODO
}