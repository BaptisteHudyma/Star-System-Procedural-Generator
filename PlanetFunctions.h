#include <vector>
#include <iostream>
#include "StarFunctions.h"
#include "Classes.h"

using namespace std;

#ifndef PLANETFUNCTIONS_H_INCLUDED
#define PLANETFUNCTIONS_H_INCLUDED

vector<Planet> CreatePlacePlanetsOnSSMeth1(Star, int);
vector<Planet> CreatePlacePlanetsOnSSMeth2(Star, int);
vector<Planet> CreatePlacePlanetsOnSSMeth3(Star, int);
vector<Planet> CreatePlacePlanetsOnSSMeth4(Star, int);

void OrderPlanetsByDistance(vector<Planet> *);

void setPlanets(Star*);
void PopulatePlanets(Star*);
int IsHabitable(float, float, float);

void DisplaySystemsCaracteristics(Star);
void DisplayAsteroidBelt(AsteroidBelt);
void sortPlanet(Planet[], int);
int GasOrRock(float, float);
vector<AsteroidBelt> PlaceAsteroidBelts(Star);

#endif // PLANETFUNCTIONS_H_INCLUDED
