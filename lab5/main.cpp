#include "x11context.h"
#include "line.h"
#include "triangle.h"
#include "image.h"
#include "matrix.h"

#include <unistd.h>
#include <iostream>

void test_lines_triangles(GraphicsContext* gc)
{
	// Run tests
	Line line(50, 50, 200, 200, GraphicsContext::RED);
	gc->drawLine(50, 50, 200, 200);
	line.draw(gc);

	Line line2(80, 70, 160, 400, GraphicsContext::GREEN);
	line2.draw(gc);

	Triangle triangle(100, 100, 50, 300, 300, 300, GraphicsContext::BLUE);
	triangle.draw(gc);

	sleep(2);
	gc->clear();
	sleep(1);

	Image image;
	image.add({&line, &line2, &triangle});
	Line line3(275, 125, 300, 500, GraphicsContext::YELLOW);
	Triangle triangle2(500, 125, 75, 275, 550, 300, GraphicsContext::BLUE);
	image.add(&line3).add(&triangle2);
	image.draw(gc);

	std::cout << line << std::endl;
	std::cout << triangle2 << std::endl;

	sleep(3);
}
 
int main(void)
{
	GraphicsContext* gc = new X11Context(800,600,GraphicsContext::BLACK);

	test_lines_triangles(gc);

	delete gc;
 
	return 0;
}