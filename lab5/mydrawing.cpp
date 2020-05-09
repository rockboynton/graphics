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

    // print instructions
    std::cout << "Basic drawing program instructions:" << std::endl;
    std::cout << "Select color using numbers:" << std::endl;
    std::cout << "    1 - RED" << std::endl;
    std::cout << "    2 - YELLOW" << std::endl;
    std::cout << "    3 - GREEN" << std::endl;
    std::cout << "    4 - BLUE" << std::endl;
    std::cout << "    5 - CYAN" << std::endl;
    std::cout << "    6 - MAGENTA" << std::endl;
    std::cout << "    7 - BLACK" << std::endl;
    std::cout << "    8 - WHITE" << std::endl;
    std::cout << "    9 - GRAY" << std::endl;
    std::cout << "Use the following commands to enter a draw mode:" << std::endl;
    std::cout << "    l - line drawing" << std::endl;
    std::cout << "        Start line by clicking and dragging" << std::endl;
    std::cout << "        Release to complete line" << std::endl;
    std::cout << "    p - point drawing" << std::endl;
    std::cout << "        Click to draw point" << std::endl;
    std::cout << "    t - triangle drawing" << std::endl;
    std::cout << "        Start triangle by clicking and dragging" << std::endl;
    std::cout << "        Release to select second point" << std::endl;
    std::cout << "        Click again to complete triangle" << std::endl;
    std::cout << "    o - polygon drawing" << std::endl;
    std::cout << "        Start polygon by clicking and dragging" << std::endl;
    std::cout << "        Release to select second point" << std::endl;
    std::cout << "        Click again to select each other point" << std::endl;
    std::cout << "        Press 'c' to complete the polygon" << std::endl;
    std::cout << "File IO:" << std::endl;
    std::cout << "    d - load image from image.txt" << std::endl;
    std::cout << "    s - save image to image.txt" << std::endl;
    std::cout << "Additional commands:" << std::endl;
    std::cout << "    x - clear screen / delete image" << std::endl;
    std::cout << "    esc - stop drawing shape" << std::endl;
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
    // points.back().first = x;
    // points.back().second = y;

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
            gc->setMode(GraphicsContext::MODE_XOR);
            gc->drawLine(x,y,x,y);
            dragging = true;
            break;      
        case TRIANGLE_L2:
            print_points();
            complete_polygon(gc, points.back().first, points.back().second);
            image.add(std::make_shared<Triangle>(points[0].first, points[0].second, 
                                                 points[1].first, points[1].second, 
                                                 points[2].first, points[2].second, 
                                                 color));
            points.clear(); 
            points.emplace_back(0, 0); points.emplace_back(0, 0);
            dragging = false; 
            break;
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
            gc->drawLine(points.back().first,points.back().second,
                 points.end()[-2].first, points.end()[-2].second);
            points.emplace_back(x, y);
            dragging = true;
            state = TRIANGLE_L2;
            break;
        case POLYGON_L1:
            gc->drawLine(points.back().first,points.back().second,
                 points.end()[-2].first, points.end()[-2].second);
            points.emplace_back(x, y);
            dragging = true;
            state = POLYGON_LN;
            break; 
        case POLYGON_LN:
            dragging = true;
            break;
        case TRIANGLE_L2:
            state = TRIANGLE_L1;
            break;
        case POINT:
            break;
    }
    return;
}

void MyDrawing::mouseMove(GraphicsContext* gc, int x, int y)
{
    if (!dragging) return;
    switch (state) {
        case LINE:
        case TRIANGLE_L1:
        case POLYGON_L1:
            xor_line(gc, x, y);
            break;
        case TRIANGLE_L2:
        case POLYGON_LN:
            rubberband_poly(gc, x, y);
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
        case 65307: // esc key undraws last line and exits drawing mode
            gc->setMode(GraphicsContext::MODE_XOR);
            gc->setColor(color);
            gc->drawLine(points.back().first,points.back().second,
                         points.end()[-2].first, points.end()[-2].second);
            points.clear();
            points.emplace_back(0, 0); points.emplace_back(0, 0);
            dragging = false;
            if (state == POLYGON_LN) state = POLYGON_L1;
            if (state == TRIANGLE_L2) state = TRIANGLE_L1;
            break;
        case 'x':
            image.erase();
            gc->clear();
            points.clear();
            points.emplace_back(0, 0); points.emplace_back(0, 0);
            dragging = false;
            if (state == POLYGON_LN) state = POLYGON_L1;
            if (state == TRIANGLE_L2) state = TRIANGLE_L1;
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
                complete_polygon(gc, points.back().first, points.back().second);
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

void MyDrawing::complete_polygon(GraphicsContext* gc, int x, int y)
{
    gc->setMode(GraphicsContext::MODE_XOR);
    gc->setColor(color);

    // undraw old lines
    gc->drawLine(points.back().first,points.back().second,
                 points.end()[-2].first, points.end()[-2].second);
    gc->drawLine(points.back().first,points.back().second,
                 points[0].first, points[0].second);

    // update 
    points.back().first = x;
    points.back().second = y;

    // go back to COPY mode
    gc->setMode(GraphicsContext::MODE_NORMAL);
    
    // new line drawn in copy mode
    gc->drawLine(points.back().first,points.back().second,
                 points.end()[-2].first, points.end()[-2].second);
    gc->drawLine(points.back().first,points.back().second,
                 points[0].first, points[0].second);
}

void MyDrawing::print_points()
{
    std::cout << points.size();
    for (auto& point : points) {
        std::cout << "(" << point.first << "," << point.second << ")";
    }
    std::cout << std::endl;
}