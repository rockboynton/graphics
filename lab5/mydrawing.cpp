#include "mydrawing.h"
#include "gcontext.h"
#include "polygon.h"

#include <fstream>

// Constructor
MyDrawing::MyDrawing(int dx, int dy) : vc(dx, dy)
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
    std::cout << "Transformations:" << std::endl;
    std::cout << "    m - move around the image (pan/translate)" << std::endl;
    std::cout << "        Click then drag to start panning" << std::endl;
    std::cout << "        Realease to end translation" << std::endl;
    std::cout << "    z - zoom on the image (scale)" << std::endl;
    std::cout << "        Click then drag to scaling" << std::endl;
    std::cout << "        right - widen image" << std::endl;
    std::cout << "        left - narrow image" << std::endl;
    std::cout << "        up - lengthen image" << std::endl;
    std::cout << "        down - squish image" << std::endl;
    std::cout << "        diagonal up/right - zoom in" << std::endl;
    std::cout << "        diagonal down/left - zoom out" << std::endl;
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
    image.draw(gc, &vc);
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

    // go back to COPY mode
    gc->setMode(GraphicsContext::MODE_NORMAL);

    // new line drawn in copy mode
    gc->drawLine(points.back().first,points.back().second,
                 points.end()[-2].first, points.end()[-2].second);
}

void MyDrawing::mouseButtonDown(GraphicsContext* gc, unsigned int button, int x, int y) {
    switch (state) {
        case POINT:
        {
            points.front().first = points.back().first = x;
            points.front().second = points.back().second = y;
            copy_line(gc, x, y);
            auto model = vc.get_model_coords(std::make_unique<matrix>(matrix::coordinate(x, y)));
            image.add(std::make_shared<Line>((*model)[0][0], (*model)[1][0], 
                                             (*model)[0][0], (*model)[1][0], 
                                             color));
            break;
        }
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
        {
            complete_polygon(gc, points.back().first, points.back().second);
            auto model0 = vc.get_model_coords(std::make_unique<matrix>(
                    matrix::coordinate(points[0].first, points[0].second)));
            auto model1 = vc.get_model_coords(std::make_unique<matrix>(
                    matrix::coordinate(points[1].first, points[1].second)));
            auto model2 = vc.get_model_coords(std::make_unique<matrix>(
                    matrix::coordinate(points[2].first, points[2].second)));
            image.add(std::make_shared<Triangle>((*model0)[0][0], (*model0)[1][0],
                                                 (*model1)[0][0], (*model1)[1][0], 
                                                 (*model2)[0][0], (*model2)[1][0], 
                                                 color));
            points.clear(); 
            points.emplace_back(0, 0); points.emplace_back(0, 0);
            dragging = false; 
            break;
        }
        case POLYGON_LN:
            points.emplace_back(x, y);
            copy_line(gc, x, y);
            dragging = true;
            break;
        case TRANSLATING:
        case SCALING:
            points.front().first = points.back().first = x;
            points.front().second = points.back().second = y;
            dragging = true;
            break;
    }
    return;
}

void MyDrawing::mouseButtonUp(GraphicsContext* gc, unsigned int button, int x, int y)
{
    switch (state) {
        case LINE:
        {
            copy_line(gc, x, y);
            auto model0 = vc.get_model_coords(std::make_unique<matrix>(
                    matrix::coordinate(points[0].first, points[0].second)));
            auto model1 = vc.get_model_coords(std::make_unique<matrix>(
                    matrix::coordinate(points[1].first, points[1].second)));
            image.add(std::make_shared<Line>((*model0)[0][0], (*model0)[1][0],
                                             (*model1)[0][0], (*model1)[1][0], 
                                             color));
            dragging = false;
            break;
        }
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
        case TRANSLATING:
        case SCALING:
            dragging = false;
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
        case TRANSLATING:
            points.back().first = x;
            points.back().second = y;
            vc.translate(points[1].first - points[0].first, -(points[1].second - points[0].second));
            gc->clear();
            paint(gc);
            points.front().first = x;
            points.front().second = y;
            break;
        case SCALING:
            points.back().first = x;
            points.back().second = y;
            int dx = points[1].first - points[0].first;
            int dy = -(points[1].second - points[0].second);
            double scale_x = dx > 0 ? (dx + 100) / 100.0 : 100.0 / (100 - dx);
            double scale_y = dy > 0 ? (dy + 100) / 100.0 : 100.0 / (100 - dy);
            vc.scale(scale_x, scale_y);
            gc->clear();
            paint(gc);
            points.front().first = x;
            points.front().second = y;
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
                    auto model = vc.get_model_coords(std::make_unique<matrix>(
                            matrix::coordinate(point.first, point.second)));
                    poly->add_vertex((*model)[0][0], (*model)[1][0]);
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
        case 'm':
            state = TRANSLATING;
            break;
        case 'z':
            state = SCALING;
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

void MyDrawing::save_image()
{
    std::ofstream fout;
    fout.open("image.txt");
    image.out(fout);
    std::cout << "Image saved in image.txt" << std::endl;
    fout.close();
}

void MyDrawing::load_image(GraphicsContext* gc)
{
    image.erase();
    gc->clear();
    std::ifstream fin("image.txt");
    if (fin){
        image.in(fin);
        gc->setMode(GraphicsContext::MODE_NORMAL);
        image.draw(gc, &vc);
        std::cout << "Image loaded from image.txt" << std::endl;
    } else std::cout << "image.txt not in working directory" << std::endl;
    fin.close();
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
    
    // new lines drawn in copy mode
    gc->drawLine(points.back().first,points.back().second,
                 points.end()[-2].first, points.end()[-2].second);
    gc->drawLine(points.back().first,points.back().second,
                 points[0].first, points[0].second);
}
