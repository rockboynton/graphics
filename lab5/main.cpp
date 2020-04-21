#include "x11context.h"
#include <unistd.h>
#include <iostream>
 
int main(void)
{
	GraphicsContext* gc = new X11Context(800,600,GraphicsContext::WHITE);
 
	int a[2] = {1,2};

    auto [x,y] = a; // creates e[2], copies a into e, then x refers to e[0], y refers to e[1]

    std::cout << x << y << std::endl;

	delete gc;
 
	return 0;
}