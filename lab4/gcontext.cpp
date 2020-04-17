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

void GraphicsContext::bresenham(int x0, int y0, int x1, int y1, int dx, int dy, bool reversed)
{
	double slope = (double)dy/dx;
	// x increment - need to know which way to go
	int incx = std::abs(dx)/dx;  // will be 1 or -1
	
	for (int x = x0; x != x1; x += incx)
	{
		reversed ? setPixel(y0+slope*(x-x0),x) : setPixel(x,y0+slope*(x-x0));
	}
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
	
	// find slope
	int dx = x1-x0;
	int dy = y1-y0;
	
	// make sure we actually have a line
	if (dx != 0 || dy !=0)
	{
		// slope < 1?
		if (std::abs(dx)>std::abs(dy))
		{	// iterate over x
			bresenham(x0, y0, x1, y1, dx, dy, false);
		} // end of if |slope| < 1 
		else 
		{	// iterate over y
			bresenham(y0, x0,y1, x1, dy, dx, true);	
		} // end of else |slope| >= 1
		// loop ends on iteration early - catch endpoint
		setPixel(x1,y1);
	} // end of if it is a real line (dx!=0 || dy !=0)
	return;
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

