CC = g++
CFLAGS = -std=c++17 -c -MMD -Wall
LFLAGS = -lX11
SOURCES = line.cpp shape.cpp x11context.cpp gcontext.cpp main.cpp 
OBJECTS = $(SOURCES:.cpp=.o)
EXCECUTABLE = main

all: $(EXCECUTABLE) $(SOURCES)

$(EXCECUTABLE): $(OBJECTS)
	$(CC) $(LFLAGS) -o $@ $(OBJECTS)

-include *.d

%.o: %.cpp
	$(CC) $(CFLAGS) $<

clean: 
	rm -f $(EXCECUTABLE)
	rm -f $(OBJECTS)
	rm -f *.d