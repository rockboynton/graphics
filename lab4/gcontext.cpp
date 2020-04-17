/* This is an abstract base class representing a generic graphics
 * context.  Most implementation specifics will need to be provided by
 * a concrete implementation.  See header file for specifics. */

#define _USE_MATH_DEFINES	// for M_PI
#include <cmath>	// for trig functions
#include "gcontext.h"	
#include <iostream>

/*
 * Destructor - does nothing
 */
GraphicsContext::~GraphicsContext()
{
	// nothing to do
	// here to insure subclasses handle destruction properly
}

/* This is a naive implementation that uses floating-point math
 * and "setPixel" which will need to be provided by the concrete
 * implementation.
 * 
 * Parameters:
 * 	x0, y0 - origin of line
 *  x1, y1 - end of line
 * 
 * Returns: void
 */
void GraphicsContext::drawLine(int x0, int y0, int x1, int y1)
{
	int dx, dy;
    int stepx, stepy;

    dx = x1 - x0;
    dy = y1 - y0;

    if (dy < 0) 
	{ 
		dy = -dy; 
		stepy = -1; 
	} 
	else 
	{ 
		stepy = 1; 
	}

    if (dx < 0) 
	{ 
		dx = -dx; 
		stepx = -1; 
	} 
	else 
	{ 
		stepx = 1; 
	}

    dy <<= 1; /* dy is now 2*dy */
    dx <<= 1; /* dx is now 2*dx */
    
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
            setPixel(x0, y0);
        }
    }
}



/* This is a naive implementation that uses floating-point math
 * and "setPixel" which will need to be provided by the concrete
 * implementation.
 * 
 * Parameters:
 * 	x0, y0 - origin/center of circle
 *  radius - radius of circle
 * 
 * Returns: void
 */
void GraphicsContext::drawCircle(int x0, int y0, unsigned int radius)
{
	// This is a naive implementation that draws many line
	// segments.  Also uses floating point math for poor performance

	// also, large circles will be "jagged"
	
	// start at 0 degrees
	int oldx = radius;
	int oldy = 0;

	// go from 1 to 360 degrees
	for (int segment =1; segment<=360; segment += 1)
	{
		int newx = std::cos(segment*M_PI/180)*radius;
		int newy = std::sin(segment*M_PI/180)*radius;

		// hit four quadrants
		drawLine(x0+oldx,y0+oldy,x0+newx,y0+newy);
		
		oldx = newx;
		oldy = newy;
		
	}
	
	return;	
}

void GraphicsContext::endLoop()
{
	run = false;
}

