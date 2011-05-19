all: lev_sim

lev_sim: passenger.cpp floor.cpp building.cpp elevator.cpp main.cpp building.h elevator.h floor.h passenger.h
	g++ -o $@ passenger.cpp floor.cpp building.cpp elevator.cpp main.cpp -g -Wall
