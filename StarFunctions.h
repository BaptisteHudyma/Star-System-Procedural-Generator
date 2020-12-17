
#include <string>
#include <iostream>
#include <math.h>
#include "Classes.h"

using namespace std;


#ifndef STARFUNCTIONS_H_INCLUDED
#define STARFUNCTIONS_H_INCLUDED


int DeterminStarClass (int);
int DetermineStarType ();
float getFrostZoneLimit (Star);

void CreateStar (Star*);
void CreateMultipleStarSystem (Star *);
void DisplayStarCarac (Star);
void DisplayDoubleStar (Star, bool);

float guessStarMassWithTemp (unsigned int);
float guessStarMassWithLum (float);
int RandomInt (int, int);
float RandomFloat (float, float);
int getTemperatureClassification ();
unsigned int getStarTemperature (int, int);
float StarLuminosity (float, unsigned int);
float StarRadius (unsigned int, float);
float StarLuminosityFromClassification (int, int);

float getStarLuminosity (int, int);
float mapValueX (float, float, float, float, float);
void spectral_color (double &,double &,double &,double);


#endif // STARFUNCTIONS_H_INCLUDED
