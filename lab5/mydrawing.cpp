#include "mydrawing.h"
#include "gcontext.h"
#include "polygon.h"

// Constructor
MyDrawing::MyDrawing()
{
    dragging = false;

    // TODO print instructions

    return;
}

void MyDrawing::paint(GraphicsContext* gc)
{
    image.draw(gc);
    return;
}

void MyDrawing::xor_line(GraphicsContext* gc, int x, int y)
{
    gc->setMode(GraphicsContext::MODE_XOR);
    // mouse moved - "undraw" old line, then re-draw in new position
    // old line undrawn
    gc->setColor(color);
    gc->drawLine(points[current_pos-1].first,points[current_pos-1].second,
                points[current_pos].first, points[current_pos].second);
    // update
    points[current_pos].first = x;
    points[current_pos].second = y;
    // new line drawn
    gc->drawLine(points[current_pos-1].first,points[current_pos-1].second,
                points[current_pos].first, points[current_pos].second);
}

void MyDrawing::copy_line(GraphicsContext* gc, int x, int y)
{
    // undraw old line
    gc->drawLine(points[current_pos-1].first,points[current_pos-1].second,
                points[current_pos].first, points[current_pos].second);
    // just in x and y here do not match x and y of last mouse move
    points[current_pos].first = x;
    points[current_pos].second = y;
    // go back to COPY mode
    gc->setMode(GraphicsContext::MODE_NORMAL);
    gc->setColor(color);
    // new line drawn in copy mode
    gc->drawLine(points[current_pos-1].first,points[current_pos-1].second,
                points[current_pos].first, points[current_pos].second);
}

void MyDrawing::mouseButtonDown(GraphicsContext* gc, unsigned int button, int x, int y) {
    // mouse button pushed down
    // - clear context
    // - set origin of new line // - set XOR mode for rubber-banding
    // - draw new line in XOR mode. Note, at this point, the line is
    // degenerate (0 length), but need to do it for consistency
    switch (state) {
        case LINE:
        case TRIANGLE_L1:
            points.emplace_back(x, y);
            current_pos++;
            points[current_pos-1].first = points[current_pos].first = x;
            points[current_pos-1].second = points[current_pos].second = y;
            break;
        case POLYGON_LN:

            break;
        case TRIANGLE_L2:
            copy_line(gc, x, y);

            state = TRIANGLE_L1;
        case POINT:
        case POLYGON_L1:
            points.emplace_back(x, y);
            current_pos++;
            points[current_pos-1].first = points[current_pos].first = x;
            points[current_pos-1].second = points[current_pos].second = y;
            break;
    }
    return;
}

void MyDrawing::mouseButtonUp(GraphicsContext* gc, unsigned int button, int x, int y)
{
    switch (state) {
        case LINE:
            xor_line(gc, x, y);
            break;
        case TRIANGLE_L1:
            xor_line(gc, x, y);
            state = TRIANGLE_L2;
            break;
        case POLYGON_LN:
            xor_line(gc, x, y);
            state = POLYGON_LN;
            break;
        case TRIANGLE_L2:
            copy_line(gc, x, y);
            state = TRIANGLE_L1;
        case POINT:
        case POLYGON_L1:
            copy_line(gc, x1, y1);
            image.add(std::make_shared<Line>(x1, y1, x1, y1, color));
            break;
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
            state = TRIANGLE_L1;
            break;
        case 'o':
            state = POLYGON_L1;
            break;
        case 'c':
            if (state == POLYGON_LN) { // close polygon
                gc->setColor(color);
                gc->drawLine(x0, y0, x1, y1);
                ((Polygon*) current_shape)->add_vertex(x1, y1);
                image.add(current_shape);
            }
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