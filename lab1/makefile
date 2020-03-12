SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXCECUTABLE = main

main: $(OBJECTS)
	g++ -o $(EXCECUTABLE) $(OBJECTS)

main.o: main.cpp
	g++ -c main.cpp

clean: 
	rm -f $(OBJECTS)
	rm -f $(EXCECUTABLE)