
CXX = g++
SRC = src
BIN = bin
OBJ = obj

CFLAGS = `pkg-config --cflags --libs gflags libglog`
CFLAGS += -std=c++11
CFLAGS += -I./include


$(BIN)/assignment2:$(OBJ)/input.o $(OBJ)/main.o
	$(CXX) $^ -o $@ $(CFLAGS)

$(OBJ)/input.o:$(SRC)/input.cpp
	$(CXX) $^ -c -o $@ $(CFLAGS)
$(OBJ)/main.o:$(SRC)/main.cpp
	$(CXX) $^ -c -o $@ $(CFLAGS)

clean:
	rm bin/assignment2
	rm obj/*
