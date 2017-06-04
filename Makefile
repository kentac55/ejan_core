CXX = g++
CXXFLAGS = `pkg-config --cflags opencv` -O2 -g -MD -MMD -Wall -Wextra -Winit-self -Wno-missing-field-initializers
LDFLAGS =
LIBS = `pkg-config --libs opencv`
INCLUDE =
SRC_DIR = ./src
OBJ_DIR = ./build
SOURCES = $(shell ls $(SRC_DIR)/*.cpp)
OJBS = $(subst $(SRC_DIR), $(OBJ_DIR), $(SOURCES:.cpp=.o))
TARGET = ejan
DEPENDS = $(OBJS:.o = .d)


.PHONY: all clean

ejan: ejan.o
	$(CXX) -o $@ $(LIBS) ejan.o

ejan.o: ejan.cpp
	$(CXX) -c $(CXXFLAGS) ejan.cpp

ejanM: ejanM.o
	$(CXX) -o $@ $(LIBS) -fopenmp ejanM.o

ejanM.o: ejan.cpp
	$(CXX) -c $(CXXFLAGS) -fopenmp ejan.cpp

clean2:
	rm -f ejan.o ejanM.o
