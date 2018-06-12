CC = g++
CFLAGSS = -Wall -ansi -O2 -std=c++11
SOURCES = main.cpp src/game_board.cpp src/game_control.cpp
EXECUTABLE = main

all:
	$(CC) $(CFLAGSS) $(SOURCES) -o $(EXECUTABLE)