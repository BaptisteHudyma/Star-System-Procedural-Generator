CC = g++
all: galaxy

galaxy: main.o PlanetCreationReferenceFunctions.o PlanetFunctions.o StarFunctions.o
	$(CC) -o galaxy main.o PlanetCreationReferenceFunctions.o PlanetFunctions.o StarFunctions.o

main.o : main.cpp StarFunctions.h PlanetFunctions.h Classes.h
	$(CC) -c main.cpp

PlanetCreationReferenceFunctions.o : PlanetCreationReferenceFunctions.cpp PlanetFunctions.h
	$(CC) -c PlanetCreationReferenceFunctions.cpp

PlanetFunctions.o : PlanetFunctions.cpp PlanetFunctions.h StarFunctions.h
	$(CC) -c PlanetFunctions.cpp

StarFunctions.o : StarFunctions.cpp PlanetFunctions.h StarFunctions.h
	$(CC) -c StarFunctions.cpp

clean :
	rm −f ∗˜ ∗ . o
