#include "x11context.h"
#include "line.h"
#include "triangle.h"
#include "image.h"
#include "matrix.h"

#include <unistd.h>
#include <iostream>
 
int main(void)
{
	GraphicsContext* gc = new X11Context(800,600,GraphicsContext::BLACK);

	// Run tests
	Line line(50, 50, 200, 200, GraphicsContext::RED);
	// gc->drawLine(50, 50, 200, 200);
	line.draw(gc);

	// Line line2(80, 70, 160, 400, GraphicsContext::GREEN);
	// line2.draw(gc);

	// line2 = line;
	// line2.draw(gc);

	// Triangle triangle(100, 100, 50, 300, 300, 300, GraphicsContext::RED);

	sleep(3);
	delete gc;
 
	return 0;
}