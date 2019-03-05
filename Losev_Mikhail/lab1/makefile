all: main.o field.o
	g++ main.o field.o -o main
main.o: main.cpp field.h field.h
	g++ -c main.cpp
field.o: field.cpp field.h field.h
	g++ -c field.cpp


