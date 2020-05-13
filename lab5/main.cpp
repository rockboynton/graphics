#include "x11context.h"
#include "line.h"
#include "triangle.h"
#include "image.h"
#include "matrix.h"
#include "mydrawing.h"

#include <unistd.h>
#include <iostream>
#include <fstream>

 
int main(void)
{
	GraphicsContext* gc = new X11Context(800,600,GraphicsContext::BLACK);
	gc->setColor(GraphicsContext::GREEN); // set default to green

	// make a drawing
	MyDrawing md(gc->getWindowWidth(), gc->getWindowHeight());

	// start event loop - this function will return when X is clicked on window
	gc->runLoop(&md);

	delete gc;
	return 0;
}