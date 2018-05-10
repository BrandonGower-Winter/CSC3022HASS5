#Brandon Gower-Winter
#Makefile for Assignment 4 CSC3022H
#Originally created on 26/02/2018

CC := g++
CCFLAGS := -std=c++11
SRCDIR := src
TESTDIR := tests
BUILDDIR := build
EXECUTABLE := bin/imageops
TESTECUTABLE := bin/tests

SRCFLEXT := cpp

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCFLEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCFLEXT)=.o))

$(EXECUTABLE) : $(OBJECTS)
	@echo Starting Link...
	$(CC) $(CCFLAGS)  $^ -o $(EXECUTABLE)
	@echo Link Complete

$(BUILDDIR)/%.o : $(SRCDIR)/%.$(SRCFLEXT)
	$(CC) $(CCFLAGS) -c -o $@ $<

run:
	./$(EXECUTABLE)

test:
	@echo Compiling...
	$(CC) $(CCFLAGS) -c -o $(BUILDDIR)/Image.o $(SRCDIR)/Image.cpp
	$(CC) $(CCFLAGS) -c -o $(BUILDDIR)/Filter.o $(SRCDIR)/Filter.cpp
	$(CC) $(CCFLAGS) -c -o $(BUILDDIR)/UnitTests.o $(TESTDIR)/UnitTests.cpp
	@echo Compilation Complete
	@echo Linking...
	$(CC) $(CCFLAGS) -o $(TESTECUTABLE) $(BUILDDIR)/Image.o $(BUILDDIR)/Filter.o $(BUILDDIR)/UnitTests.o
	@echo Linking Complete

runTests:
	./$(TESTECUTABLE)

clean:
	rm -f build/*.o
	rm -f ./bin/*
