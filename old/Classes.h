#ifndef CLASSES_H_INCLUDED
#define CLASSES_H_INCLUDED

#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

#define OUTER_LIMIT_COEFF 60.0


using namespace std;

float RandomFloat (float, float);
int RandomInt (int, int);

class Planet {
	private :
		int PlanetType; //0 rocky, 1 gaze, 2 gas giant
		string Type;    //rocky, gaz, gaz giant;

		//orbital
		float SemiMajor;  //semimajor axis
		float Apoapsis;     //farther position to sun
		float Periabsis;    //closer position to sun
		float Velocity;     //orbital velocity

		float Oinclination; //-2° <-> 2° for planets
		float LoAN; //Longitude of the Ascending Node
		float AoP;  //Argument of Periapsis

		//Physical (express in earth values)
		float Mass;
		float Density;
		float Radius;
		float Gravity;

		//Local changes
		float AxeTilt;
		float minTemp;
		float maxTemp;


		vector<Planet> MajorMoons;   //major moons that this planet have
		vector<Planet> MinorMoons;   //minor moons that this planet have


	public :
		int Habitable;  //0 too close to sun, 1 in habitable, 2 out of habitable
		float *Composition;   //5 elements -> 0 : iron, 1 : MgSi, 2 : Water, 3 : Hydrogen, 4 : Helium
		float OrbitalPeriod;    //time to rotate around the sun once
		float HillSphere;       //hill sphere limit, in AU
		float Albedo;           //planet reflectivity (changeover time)
		float GreenHouse;

		float eccentricity;

		unsigned int PlanetSeed;

		int MajorMoonNumber;
		int MinorMoonNumber;

		float Temp;

		bool RingSystem;    //true : ring system, false no ring system

		float RocheLimit;   //minimal distance for a satellite hold together by tensile strength
		Planet ()
		{
			MajorMoons = vector<Planet> ();
			MinorMoons = vector<Planet> ();
			HillSphere = -1.0;
			PlanetSeed = RandomInt (1, INT_MAX);
			Temp = 0;
		};
		void setOrbitalRadius (float Oradius) {SemiMajor = Oradius;};
		void setPlanetType (int TypeS) {
			PlanetType = TypeS;
			switch (TypeS){
				case 0:
					Type = "Rocky";
					break;
				case 1:
					Type = "Gas";
					break;
				case 2:
					Type = "Gas giant";
					break;
				default:
					printf ("\n%d planetary type is not define\n", TypeS);
					exit (-5);
					break;
			}
		};
		void setType (string TypeSet) {Type = TypeSet;};
		void setOrbitalValues (float InnerLimit, float OuterLimit, float StarMass);
		void setPhysicalValues (float StarLum, float StarMass)
		{
			switch (PlanetType)
			{
				case 0:
					SetRockyPlanetPhysical(StarLum, StarMass);
					break;
				case 1:
					SetGasPlanetPhysical(StarLum, StarMass);
					break;
				case 2:
					SetGasGiantPhysical(StarLum, StarMass);
					break;
				default :
					printf ("\n%d planetary type is not define\n", PlanetType);
					exit (0);
					break;
			}
		}
		void SetRockyPlanetPhysical (float StarLum, float StarMass);
		void SetGasPlanetPhysical (float StarLum, float StarMass);
		void SetGasGiantPhysical (float StarLum, float StarMass);

		float getMinTemperature (float StarLum)
		{
			minTemp = pow(StarLum * (1-Albedo) / pow (Apoapsis , 2.0) , 1.0/4.0) * 263.0 + GreenHouse;
			return minTemp;
		};
		float getMaxTemperature (float StarLum)
		{
			maxTemp = pow(StarLum * (1-Albedo) / pow(Periabsis , 2.0) , 1.0/4.0) * 263.0 + GreenHouse;
			return maxTemp;
		};

		float getHillSphereLimit(float PrimaryMass)
		{
			return HillSphere = (float)SemiMajor * (1 - eccentricity) * pow( ( ((float)Mass)/332946.0487) / (3 * PrimaryMass) , 1.0/3.0 );
		};
		int getPlanetType() {return PlanetType;};
		float getEscapeVelocity() { return sqrt(Gravity * Radius) * 11.2; };    //in km/s
		float getOrbitalDistance() { return SemiMajor; };
		void DisplayPlanet(float StarMass);
		string getType() {return Type;};
		float getMass() {return Mass;};
};


class AsteroidBelt{
	private:
		float MidRangeOrbit;    //orbit of the middle of the belt
		float Width;            //width of the asteroid belt

		float InnerEdge;        //inner edge of asteroid belt
		float OuterEdge;        //outer edge of asteroid belt

	public:
		void setMidRange(float MR){ MidRangeOrbit = MR; };
		void setWidth(float Wdth)
		{
			Width = Wdth;
			InnerEdge = MidRangeOrbit - Width/2;
			OuterEdge = MidRangeOrbit + Width/2;
		};

		float getMidRange() {return MidRangeOrbit;};
		float getWidth() {return Width;};
		float getInnerEdge() {return InnerEdge;};
		float getOuterEdge() {return OuterEdge;};
};


class Star{
	private :
		unsigned int Temperature;
		char Type;              //O, B, A, ....
		string Class;             //0, I, II, III, ...
		int LuminosityClass;    //0-9
		int ColorSpectrum;      //in Nm
		float FrostZone;
		float HabitableInferieur;
		float HabitableSuperieur;
		float RocheLimit;
		vector<Planet> System;
		vector<AsteroidBelt> AstBelt;

		//size parameter (in solar units)
		float Density;
		float Volume;
		float Radius;
		float Luminosity;
		float Mass;


		int ClassInt;
		int TypeInt;

	public :
		float OrbitalRadius;    //if it's a multiple star system this value is not 0
		float eccentricity;
		float SemiMajor;
		float apoabsis;
		float periabsis;
		float OuterEdge;

		vector<Star> Companions;  //contain the stars paired if this system is a multiple star system

		Star()
		{
			Companions = vector<Star>();
			eccentricity = 0;
			SemiMajor = 0;
			apoabsis = 0;
			periabsis = 0;

			OuterEdge = 0;
			OrbitalRadius = 0;
			HabitableInferieur = 0;
			HabitableSuperieur = 0;
			FrostZone = 0;
			RocheLimit = 0;
			System = vector<Planet>();
			AstBelt = vector<AsteroidBelt>();
		}

		void setTemperature(unsigned int Temp) {Temperature = Temp;};
		void setType(char Typeset) {Type = Typeset;};
		void setClass(string ClassSet) {Class = ClassSet;};
		void setRadius(float diam) {Radius = diam;};
		void setRocheLimit(float RL) {RocheLimit = RL;};
		void setLuminosity(float Lum) {Luminosity = Lum;};
		void setLuminosityClass(int LumClass) {LuminosityClass = LumClass;};
		void setSpectrum(int Spec) {ColorSpectrum = Spec;};
		void setMass(float StarMass) {Mass = StarMass;};
		void setSystem(vector<Planet> Sys) {System = Sys;};
		void setAsteroidBelt(vector<AsteroidBelt> Ast) {AstBelt = Ast;};

		void setVolume(float vol) {Volume = vol;};
		void setDensity(float den) {Density = den;};

		void setClassInt(int ClassI) {ClassInt = ClassI;};
		void setTypeInt(int TypeI) {TypeInt = TypeI;};


		unsigned int getTemperature() { return Temperature;};
		char getType() {return Type;};
		string getClass() { return Class; };
		float getRadius() { return Radius; };
		float getLuminosity() { return Luminosity; };
		int getLuminosityClass() { return LuminosityClass; };
		int getSpectrum() { return ColorSpectrum; };
		float getMass() {return Mass;};
		vector<Planet> getSystem() { return System; };
		vector<AsteroidBelt> getAsteroidBelt() {return AstBelt;};

		float getVolume() {return Volume;};
		float getDensity() {return Density;};

		float getOuterLimit(){
			if(OuterEdge <= 0)
				OuterEdge = Mass*OUTER_LIMIT_COEFF;
			if(OuterEdge > 601)
				OuterEdge = 601;
			return OuterEdge;
		}
		float getRocheLimit(){
			if(RocheLimit <= 0)
			{
				if(Mass <= 1 || Luminosity <= 1)
					RocheLimit = 0.1*Mass;
				else
					RocheLimit = 0.1*sqrt((float)Luminosity);
				if(getOuterLimit() < RocheLimit)
				{
					float Tempo = RocheLimit;
					RocheLimit = OuterEdge;
					OuterEdge = Tempo;
				}
			}

			return RocheLimit;
		};
		float getFrostZone(){
			if(FrostZone <= 0)
				FrostZone = 4.85*sqrt((float)Luminosity);
			return FrostZone;
		};
		float getHabitableZoneInf(){
			if(HabitableInferieur <= 0)
				HabitableInferieur = sqrt( (float)Luminosity ) * 0.75;
			return HabitableInferieur;
		}
		float getHabitableZoneSup(){
			if(HabitableSuperieur <= 0)
				HabitableSuperieur = sqrt( (float)Luminosity ) * 1.37;
			return HabitableSuperieur;
		}

		float getHillSphere(float MassOfCloseStar)
		{
			return SemiMajor * (1-eccentricity) * pow( Mass/(3.0*MassOfCloseStar) , 1.0/3.0 );
		}

		int getClassInt() {return ClassInt;};
		int getTypeInt () {return TypeInt;};
};


#endif // CLASSES_H_INCLUDED

