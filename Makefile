
CXX = g++
SRC = src
BIN = bin
OBJ = obj

#CFLAGS = `pkg-config --cflags --libs gflags libglog`
#CFLAGS = -std=c++11
CFLAGS = -g -I./include


$(BIN)/assignment2:$(OBJ)/input.o $(OBJ)/main.o $(OBJ)/common.o $(OBJ)/cluster.o
	$(CXX) $^ $(CFLAGS) -o $@ 

$(OBJ)/input.o:$(SRC)/input.cpp
	$(CXX) $^ -c $(CFLAGS) -o $@ 
$(OBJ)/main.o:$(SRC)/main.cpp
	$(CXX) $^ -c $(CFLAGS) -o $@ 
$(OBJ)/common.o:$(SRC)/common.cpp
	$(CXX) $^ -c $(CFLAGS) -o $@ 
$(OBJ)/cluster.o:$(SRC)/cluster.cpp
	$(CXX) $^ -c $(CFLAGS) -o $@ 

clean:
	rm bin/assignment2
	rm obj/*
