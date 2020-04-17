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

/**
 * @brief Resolves the cases when the line is defined from right to left 
 * 
 * @param delta - change along an axis; will be positive after return
 * @param step - step size for an axis; will be +1 if left-to-right, -1 if right-to-left
 */
void GraphicsContext::resolveSlope(int& delta, int& step)
{
	if (delta < 0) 
	{ 
		delta = -delta; 
		step = -1; 
	} 
	else 
	{ 
		step = 1; 
	}
}

/**
 * @brief Resolves the cases when the line is defined from right to left
 * 
 * @param dx - change in x; will be positive after return
 * @param dy - change in y; will be positive after return
 * @param stepx - x step size; will be +1 if left-to-right, -1 if right-to-left
 * @param stepy - y step size; will be +1 if left-to-right, -1 if right-to-left
 */
void GraphicsContext::resolveSlope(int& dx, int& dy, int& stepx, int& stepy)
{
	resolveSlope(dy, stepy);
    resolveSlope(dx, stepx);
}

/**
 * @brief Draws a line according to the Bresenham line drawing algorithm
 * 
 * @param x0 - start x
 * @param y0 - start y
 * @param x1 - end x
 * @param y1 - end y
 */
void GraphicsContext::drawLine(int x0, int y0, int x1, int y1)
{
	int dx, dy;
    int stepx, stepy;

    dx = x1 - x0;
    dy = y1 - y0;

    resolveSlope(dx, dy, stepx, stepy);

    dy <<= 1; // dy is now 2*dy 
    dx <<= 1; // dx is now 2*dx
    
    if (dx > dy) // slope < 1?
	{ // iterate over x
        int decision = dy - (dx >> 1);
        for (int x = x0, y = y0; x != x1; x += stepx) 
		{
			setPixel(x, y);
            if (decision >= 0) {
                y += stepy;
                decision -= dx;
            }
            decision += dy;
        }
    } 
	else 
	{ // iterate over y
        int decision = dx - (dy >> 1);
        for (int y = y0, x = x0; y != y1; y += stepy) 
		{
			setPixel(x, y);
            if (decision >= 0) {
                x += stepx;
                decision -= dy;
            }
            decision += dx;
        }
    }
	setPixel(x1, y1); // set endpoint
}

void GraphicsContext::setCirclePoints(int x0, int y0, int x, int y)
{
	setPixel(x0 + x, y0 + y);
	setPixel(x0 + y, y0 + x);
	setPixel(x0 - y, y0 + x);
	setPixel(x0 - x, y0 + y);
	setPixel(x0 - x, y0 - y);
	setPixel(x0 - y, y0 - x);
	setPixel(x0 + y, y0 - x);
	setPixel(x0 + x, y0 - y);
}

void GraphicsContext::midpointCircle(int x0, int y0, unsigned int radius) 
{
	int x = radius;
    int y = 0;
    int err = 1 - radius;
 
    while (x >= y)
    {
		setCirclePoints(x0, y0, x, y);
	
		if (err <= 0)
		{
			y += 1;
			err += 2*y + 1;
		}
	
		if (err > 0)
		{
			x -= 1;
			err -= 2*x + 1;
		}
    }
}

/**
 * @brief Draws a circle using a modified bresenham line algorithm for circles
 * 
 * @param x0 - center x
 * @param y0 - center y
 * @param radius - radius of the circle
 */
void GraphicsContext::drawCircle(int x0, int y0, unsigned int radius)
{
	for (int x = 0, y = radius, decision = 1 - radius; y >= x; x++)
	{
		setCirclePoints(x0, y0, x, y);
		if (decision > 0)
		{
			y--;
			decision += 2 * x - 2 * y + 5;
		}
		else
		{
			decision += 2 * x + 3;
		}		
	}
}

void GraphicsContext::endLoop()
{
	run = false;
}

