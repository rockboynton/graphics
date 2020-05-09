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
    // mouse moved - "undraw" old line, then re-draw in new position
    gc->setMode(GraphicsContext::MODE_XOR);
    gc->setColor(color);
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
    // undraw old line
    gc->setMode(GraphicsContext::MODE_XOR);
    gc->setColor(color);
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
            image.add(std::make_shared<Line>(points.front().first, points.front().second,
                                             points.back().first, points.back().second, 
                                             color));
            break;
        case TRIANGLE_L1:
            points[0].first = points[1].first = x;
            points[0].second = points[1].second = y;
            xor_line(gc, x, y);
            state = TRIANGLE_L2;
            break;
        case LINE:
            points[0].first = points[1].first = x;
            points[0].second = points[1].second = y;
            xor_line(gc, x, y);
            break;      
        case TRIANGLE_L2:
            points.emplace_back(x, y);
            complete_polygon(gc);
            image.add(std::make_shared<Triangle>(points[0].first, points[0].second, 
                                                 points[1].first, points[1].second, 
                                                 points[2].first, points[2].second, 
                                                 color));
            state = TRIANGLE_L1;
        case POLYGON_LN:
            points.emplace_back(x, y);
            copy_line(gc, x, y);
            break;
        case POLYGON_L1:
            points[0].first = points[1].first = x;
            points[0].second = points[1].second = y;
            xor_line(gc, x, y);
            state = POLYGON_LN;
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
            break;
        case TRIANGLE_L1:
            copy_line(gc, x, y);
            state = TRIANGLE_L2;
            break;
        case POLYGON_LN:
        case TRIANGLE_L2:
            xor_line(gc, x, y);
            break;
        case POLYGON_L1:
            copy_line(gc, x, y);
            state = POLYGON_LN;
            break;
        case POINT:
            break;
    }
    return;
}

void MyDrawing::mouseMove(GraphicsContext* gc, int x, int y)
{
    if (state == POINT || state == POLYGON_L1) return;
    gc->setMode(GraphicsContext::MODE_XOR);
    gc->setColor(color);

    if (state != LINE || state != TRIANGLE_L1) {
        // undraw old lines
        gc->drawLine(points.back().first,points.back().second,
                    points.end()[-2].first, points.end()[-2].second);
        gc->drawLine(points.back().first,points.back().second,
                    points[0].first, points[0].second);
    }
    // update 
    points.back().first = x;
    points.back().second = y;

    // draw new lines
    gc->drawLine(points.back().first,points.back().second,
                 points.end()[-2].first, points.end()[-2].second);
    gc->drawLine(points.back().first,points.back().second,
                 points[0].first, points[0].second);
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
                std::cout << state << std::endl;
                complete_polygon(gc);
                auto poly = std::make_shared<Polygon>(color);
                for (auto& point : points) {
                    poly->add_vertex(point.first, point.second);
                }
                image.add(poly);
                points.clear();
                points.emplace_back(0, 0); points.emplace_back(0, 0);
                state = POLYGON_L1;
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
    // undraw old lines
    gc->setMode(GraphicsContext::MODE_XOR);
    gc->setColor(color);
    gc->drawLine(points.back().first,points.back().second,
                 points.end()[-2].first, points.end()[-2].second);

    // go back to COPY mode
    gc->setMode(GraphicsContext::MODE_NORMAL);
    
    // new line drawn in copy mode
    gc->drawLine(points.back().first,points.back().second,
                 points.end()[-2].first, points.end()[-2].second);
    gc->drawLine(points.back().first,points.back().second,
                 points[0].first, points[0].second);
}