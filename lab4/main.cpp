#include "x11context.h"
#include <unistd.h>
#include <iostream>
 
int main(void)
{
	GraphicsContext* gc = new X11Context(800,600,GraphicsContext::WHITE);
 
	// draw some lines
	// gc->setColor(GraphicsContext::GREEN);
	// gc->setPixel(10,10);
	// gc->setPixel(30,30);
	// gc->drawLine(100,100,100,500);
	// gc->setColor(GraphicsContext::RED);
	// gc->drawLine(100,500,500,500);
	// gc->setColor(GraphicsContext::BLUE);
	// gc->drawLine(500,500,500,100);
	// gc->setColor(GraphicsContext::YELLOW);
	// gc->drawLine(500,100,100,100);

	// gc->setColor(GraphicsContext::MAGENTA);
	// gc->drawCircle(300,300,200);
	// sleep(5);

	gc->setColor(GraphicsContext::RED);
	for (int i = 0; i < 50; i++)
	{
		gc->drawCircle(400,300,250+ i);
	}

	// for (int i = 0; i < 25; i++)
	// {
	// 	gc->drawCircle(400,300,200 + i);
	// }

	for (int i = 0; i < 50; i++)
	{
		gc->drawCircle(400,300, 150 + i);
	}

	// for (int i = 0; i < 25; i++)
	// {
	// 	gc->drawCircle(400,300, 100 + i);
	// }
	
	for (int i = 0; i < 50; i++)
	{
		gc->drawCircle(400,300,50 + i);
	}

	gc->setColor(GraphicsContext::BLACK);
	gc->drawLine(0,600,390,310);
	gc->drawLine(0,0,390,290);
	gc->drawLine(800,0,410,290);
	gc->drawLine(800,600,410,310);

	for (int i = 0; i < 5; i++)
	{
		gc->drawCircle(400,300,i);
	}

 	sleep(5);

	delete gc;
 
	return 0;
}