
#include <iostream>
#include <limits.h>

#include "StarFunctions.h"
#include "PlanetFunctions.h"

unsigned int InputSeed ();

#define DISPLAY_PLANETS_CARAC true      //put the value to true and every planet characteristics get display
#define DISPLAY_START_CARS true         //true displays  every planet characteristics

/*1: 27.9657  kPa O2  = Breathable oxygen.
  „1¤72: 13.98285 kPa O2  = Below allowed O2 pressure (16 kPa) and very close to hypoxia (13.3 kPa). Humans won't survive much time.
  „1¤73: 55.9314  kPa O2  = Above allowed O2 pressure (50 kPa), oxygen is toxic. Humans won't suvive much time.
  „1¤74: 139.8285 kPa O2  = Above allowed O2 pressure (50 kPa), oxygen is highly toxic. Human will die in some minutes (an hour?).*/


using namespace std;

enum {O0, I, II, III, IV, V};
enum {O, B, A, F, G, K, M, D, INDETERMINE};


//wtf multi star brown dwarf etc 148
//11321 crash   //repaired
//87731 crash   //repaired
//109171 crash  //repaired

//28004 Supergiant
//17111 Hypergiant
//close binary hypergiant 26218 (too close)
//19011 Hypergiant

//26527 Double giant habitable
//6984  Habitable moon 700  118501
//33606 Class O
//542   close double habited
//657   distant double habited
//7255  Extended double system
//70434 Big system
//87288 Habitable moon
//108356 Habitable puffy giant
//109928 6 jupiterian

//14369 outer limit in inner limit

//TODO : tidal locking -> system age
//TODO : atmosphere
//TODO : better moon generation

//TODO : correct crossing orbits
//5403 broken habitable zone WATAFUCK


int main () {
    unsigned int Seed = time (NULL)%120000;

    srand (Seed);
    //srand(1047);  //lot of crossing orbits

    printf ("Seed : %u\n", Seed);
    //876 <--> 906 spe

    Star NS = Star ();
    int multipleStars = RandomInt (0, 20);

    //multipleStars = 2;

    if (multipleStars <= 3)
    {
        CreateMultipleStarSystem (&NS); 
        DisplayDoubleStar (NS, DISPLAY_START_CARS);
    }
    else
    {
        CreateStar (&NS);
        PopulatePlanets (&NS);
        DisplayStarCarac (NS);

        cout << "\n\n" << endl;
        vector<Planet> ThisSystem = NS.getSystem ();
        DisplaySystemsCaracteristics (NS);     //display the system
        cout << "\n" << endl;
        if (DISPLAY_PLANETS_CARAC)
            for (unsigned int i = 0; i < ThisSystem.size (); i++)
                ThisSystem[i].DisplayPlanet (NS.getMass ());
    }
    cout << "\n\n" << endl;

    NS.getAsteroidBelt ().clear ();
    NS.getSystem ().clear ();

    printf ("Seed : %u\n", Seed);
    return 0;
}


unsigned int InputSeed ()
{   //ask user to input a seed
    unsigned int Seed = 0;

    while (1) {
        std::cout << "\nEnter Seed INT (positive) : ";
        scanf ("%u", &Seed);

        if ((std::cin) && (Seed >= 0) && (Seed <= INT_MAX))
            break;

        std::cin.clear ();
        std::cin.ignore (1000, '\n');
        std::cout << "Seed invalid, program terminated\n" << std::endl;
        exit (-1);
    }
    return Seed;
}


/*
   int* waveLengthToRGB(double Wavelength){
   double factor;
   double Red,Green,Blue;
   if((Wavelength >= 380) && (Wavelength<440)){
   Red = -(Wavelength - 440) / (440 - 380);
   Green = 0.0;
   Blue = 1.0;
   }else if((Wavelength >= 440) && (Wavelength<490)){
   Red = 0.0;
   Green = (Wavelength - 440) / (490 - 440);
   Blue = 1.0;
   }else if((Wavelength >= 490) && (Wavelength<510)){
   Red = 0.0;
   Green = 1.0;
   Blue = -(Wavelength - 510) / (510 - 490);
   }else if((Wavelength >= 510) && (Wavelength<580)){
   Red = (Wavelength - 510) / (580 - 510);
   Green = 1.0;
   Blue = 0.0;
   }else if((Wavelength >= 580) && (Wavelength<645)){
   Red = 1.0;
   Green = -(Wavelength - 645) / (645 - 580);
   Blue = 0.0;
   }else if((Wavelength >= 645) && (Wavelength<781)){
   Red = 1.0;
   Green = 0.0;
   Blue = 0.0;
   }else{
   Red = 0.0;
   Green = 0.0;
   Blue = 0.0;
   };
// Let the intensity fall off near the vision limits
if((Wavelength >= 380) && (Wavelength<420)){
factor = 0.3 + 0.7*(Wavelength - 380) / (420 - 380);
}else if((Wavelength >= 420) && (Wavelength<701)){
factor = 1.0;
}else if((Wavelength >= 701) && (Wavelength<781)){
factor = 0.3 + 0.7*(780 - Wavelength) / (780 - 700);
}else{
factor = 0.0;
};
int* rgb = new int[3];
double Gamma = 0.80;
double IntensityMax = 255;
// Don't want 0^x = 1 for x <> 0
rgb[0] = Red==0.0 ? 0 : (int) round(IntensityMax * pow(Red * factor, Gamma));
rgb[1] = Green==0.0 ? 0 : (int) round(IntensityMax * pow(Green * factor, Gamma));
rgb[2] = Blue==0.0 ? 0 : (int) round(IntensityMax * pow(Blue * factor, Gamma));
return rgb;
}
 */
