#include "x11context.h"
#include "line.h"
#include "triangle.h"
#include "image.h"

#include <unistd.h>
#include <iostream>
 
int main(void)
{
	GraphicsContext* gc = new X11Context(800,600,GraphicsContext::BLACK);

	// Run tests
	Line line(50, 50, 200, 200, GraphicsContext::RED);
	Line line2(80, 70, 160, 400, GraphicsContext::GREEN);
	line2 = line;
	// Triangle triangle(100, 100, 50, 300, 300, 300, GraphicsContext::RED);

	sleep(1);
	delete gc;
 
	return 0;
}