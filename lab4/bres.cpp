void lineBresenham(int x0, int y0, int x1, int y1)
{
    int dx, dy;
    int stepx, stepy;

    dx = x1 - x0;
    dy = y1 - y0;

    if (dy < 0) { dy = -dy; stepy = -1; } else { stepy = 1; }
    if (dx < 0) { dx = -dx; stepx = -1; } else { stepx = 1; }

    dy <<= 1; /* dy is now 2*dy */
    dx <<= 1; /* dx is now 2*dx */
    
    if ((0 <= x0) && (x0 < RDim) && (0 <= y0) && (y0 < RDim))
        setPixel(x0, y0);
    
    if (dx > dy) {
        int fraction = dy - (dx >> 1);
        while (x0 != x1) {
            x0 += stepx;
            if (fraction >= 0) {
                y0 += stepy;
                fraction -= dx;
            }
            fraction += dy;
            if ((0 <= x0) && (x0 < RDim) && (0 <= y0) && (y0 < RDim))
                setPixel(x0, y0);
        }
    } else {
        int fraction = dx - (dy >> 1);
        while (y0 != y1) {
            if (fraction >= 0) {
                x0 += stepx;
                fraction -= dy;
            }
            y0 += stepy;
            fraction += dx;
            if ((0 <= x0) && (x0 < RDim) && (0 <= y0) && (y0 < RDim))
                setPixel(x0, y0);
        }
    }
}