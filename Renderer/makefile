CC= gcc
LD = gcc

INCDIRS=-I./inc/
LIBDIRS=-Linc/
BINDIR=bin/
SRCDIR=src/..

CXXFLAGS= -c -g -Wall
LDFLAGS= -lm
SOURCES= $(shell find $(SRCDIR) -name '*.c')
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE= $(BINDIR)test

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CXXFLAGS) $(INCDIRS) $< -o $@


clean:
	rm $(EXECUTABLE) $(OBJECTS)
