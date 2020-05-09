#include "mydrawing.h"
#include "gcontext.h"
#include "polygon.h"

// Constructor
MyDrawing::MyDrawing()
{
    // keep at least 2 points in buffer
    points.emplace_back(0, 0); points.emplace_back(0, 0);
    color = GraphicsContext::WHITE;
    state = LINE;
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
    gc->setColor(color);

    // mouse moved - "undraw" old line, then re-draw in new position
    gc->drawLine(points.back().first,points.back().second,
                 points.end()[-2].first, points.end()[-2].second);
    // update
    points.back().first = x;
    points.back().second = y;

    // new line drawn
    gc->drawLine(points.back().first,points.back().second,
                 points.end()[-2].first, points.end()[-2].second);
}

void MyDrawing::copy_line(GraphicsContext* gc, int x, int y)
{
    gc->setMode(GraphicsContext::MODE_XOR);
    gc->setColor(color);

    // undraw old line
    gc->drawLine(points.back().first,points.back().second,
                 points.end()[-2].first, points.end()[-2].second);

    // update 
    points.back().first = x;
    points.back().second = y;

    // go back to COPY mode
    gc->setMode(GraphicsContext::MODE_NORMAL);

    // new line drawn in copy mode
    gc->drawLine(points.back().first,points.back().second,
                 points.end()[-2].first, points.end()[-2].second);
}

void MyDrawing::mouseButtonDown(GraphicsContext* gc, unsigned int button, int x, int y) {
    switch (state) {
        case POINT:
            points.front().first = points.back().first = x;
            points.front().second = points.back().second = y;
            copy_line(gc, x, y);
            image.add(std::make_shared<Line>(x, y, x, y, color));
            break;
        case TRIANGLE_L1:
        case LINE:
        case POLYGON_L1:
            points.front().first = points.back().first = x;
            points.front().second = points.back().second = y;
            xor_line(gc, x, y);
            dragging = true;
            break;      
        case TRIANGLE_L2:
            complete_polygon(gc);
            image.add(std::make_shared<Triangle>(points[0].first, points[0].second, 
                                                 points[1].first, points[1].second, 
                                                 points[2].first, points[2].second, 
                                                 color));
            
            points.clear();
            points.emplace_back(0, 0); points.emplace_back(0, 0);
            state = TRIANGLE_L1;
            dragging = false; 
        case POLYGON_LN:
            points.emplace_back(x, y);
            copy_line(gc, x, y);
            dragging = true;
            break;
    }
    return;
}

void MyDrawing::mouseButtonUp(GraphicsContext* gc, unsigned int button, int x, int y)
{
    switch (state) {
        case LINE:
            copy_line(gc, x, y);
            image.add(std::make_shared<Line>(points.front().first, points.front().second,
                                             points.back().first, points.back().second, 
                                             color));
            dragging = false;
            break;
        case TRIANGLE_L1:
            copy_line(gc, x, y);
            points.emplace_back(x, y);
            state = TRIANGLE_L2;
            dragging = true;
            break;
        case POLYGON_LN:
            dragging = true;
            break;
        case TRIANGLE_L2:
            // xor_line(gc, x, y);
            dragging = false;
            state = TRIANGLE_L1;
            break;
        case POLYGON_L1:
            points[0].first = points[1].first = x;
            points[0].second = points[1].second = y;
            xor_line(gc, x, y);
            dragging = true;
            state = POLYGON_LN;
            break;
        case POINT:
            break;
    }
    return;
}

void MyDrawing::mouseMove(GraphicsContext* gc, int x, int y)
{
    switch (state) {
        case LINE:
            if (dragging) xor_line(gc, x, y);
            break;
        case TRIANGLE_L1:
            if (dragging) xor_line(gc, x, y);
            break;
        case POLYGON_LN:
            if (dragging) rubberband_poly(gc, x, y);
            break;
        case TRIANGLE_L2:
            if (dragging) rubberband_poly(gc, x, y);
            break;
        case POLYGON_L1:
            if (dragging) xor_line(gc, x, y);
            break;
        case POINT:
            break;
    }
    return;
}

void MyDrawing::rubberband_poly(GraphicsContext* gc, int x, int y)
{
    gc->setMode(GraphicsContext::MODE_XOR);
    // undraw old lines
    gc->drawLine(points.back().first,points.back().second,
                points.end()[-2].first, points.end()[-2].second);
    gc->drawLine(points.back().first,points.back().second,
                points[0].first, points[0].second);
    // update 
    points.back().first = x;
    points.back().second = y;

    // draw new lines
    gc->drawLine(points.back().first,points.back().second,
                 points.end()[-2].first, points.end()[-2].second);
    gc->drawLine(points.back().first,points.back().second,
                 points[0].first, points[0].second);
}

void MyDrawing::keyDown(GraphicsContext* gc, unsigned int keycode)
{
    switch(keycode) {
        case 'x':
            image.erase();
            gc->clear();
            points.clear();
            points.emplace_back(0, 0); points.emplace_back(0, 0);
            dragging = false;
            if (state == POLYGON_LN) state = POLYGON_L1;
            if (state == TRIANGLE_L2) state = TRIANGLE_L2;
            break;
        case 'p':
            state = POINT;
            break;
        case 'l':
            points.clear();
            points.emplace_back(0, 0); points.emplace_back(0, 0);
            state = LINE;
            break;
        case 't': 
            points.clear();
            points.emplace_back(0, 0); points.emplace_back(0, 0);
            state = TRIANGLE_L1;
            break;
        case 'o':
            points.clear();
            points.emplace_back(0, 0); points.emplace_back(0, 0);
            state = POLYGON_L1;
            break;
        case 'c':
            if (state == POLYGON_LN) { // close polygon
                complete_polygon(gc);
                auto poly = std::make_shared<Polygon>(color);
                for (auto& point : points) {
                    poly->add_vertex(point.first, point.second);
                }
                image.add(poly);
                points.clear();
                points.emplace_back(0, 0); points.emplace_back(0, 0);
                state = POLYGON_L1;
                dragging = false;
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

void MyDrawing::complete_polygon(GraphicsContext* gc)
{
    gc->setMode(GraphicsContext::MODE_XOR);
    gc->setColor(color);

    // undraw old lines
    gc->drawLine(points.back().first,points.back().second,
                 points.end()[-2].first, points.end()[-2].second);
    gc->drawLine(points.back().first,points.back().second,
                 points[0].first, points[0].second);

    // go back to COPY mode
    gc->setMode(GraphicsContext::MODE_NORMAL);
    
    // new line drawn in copy mode
    gc->drawLine(points.back().first,points.back().second,
                 points.end()[-2].first, points.end()[-2].second);
    gc->drawLine(points.back().first,points.back().second,
                 points[0].first, points[0].second);
}