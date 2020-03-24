CC = g++
CFLAGS = -c -MMD
LFLAGS =
SOURCES = main.cpp matrix.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXCECUTABLE = matrix_test

all: $(EXCECUTABLE) $(SOURCES)

$(EXCECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)

-include *.d

%.o: %.cpp
	$(CC) $(CFLAGS) $<

clean: 
	rm -f $(EXCECUTABLE)
	rm -f $(OBJECTS)
	rm -f *.d