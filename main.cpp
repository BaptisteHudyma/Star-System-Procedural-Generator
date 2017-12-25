#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <time.h>

#include <limits.h>

#include "StarFunctions.h"
#include "PlanetFunctions.h"


using namespace std;

enum {O0, I, II, III, IV, V};
enum {O, B, A, F, G, K, M, D, INDETERMINE};

unsigned int InputSeed();

//11321 crash

//28004 Supergiant
//17111 Hypergiant
//close binary hypergiant 26218 (too close)
//19011 Hypergiant

//26527 Double giant habitable
//6984  Habitable moon 700

int main(){
    unsigned int Seed = InputSeed(); srand(Seed);
    //srand(27817);


    printf("Seed : %u\n", Rand);
    //srand(27198); //11185     //54432
    //srand(8854);         //(32210);   //17053
    //80808;
    //876 <--> 906 special stars

    //srand(17026); //204444    //20437
    //srand(6898);

    Star NS;
    int multipleStars = RandomInt(0, 20);

    if(multipleStars <= 3)  //  prob 4/21 (reality is ~1/5)
    {
        CreateMultipleStarSystem(&NS);
        DisplayDoubleStar(NS, false);   //put the value to true and every planet characteristics get display
    }
    else    //simple star system
    {
        CreateStar(&NS);        //create a star
        PopulatePlanets(&NS);   //add planets to a star
        DisplayStarCarac(NS);

        cout << "\n\n" << endl;
        vector<Planet> ThisSystem = NS.getSystem();
        DisplaySystemsCaracteristics(NS);   //display the system
        cout << "\n" << endl;
        if(false)          //put the value tu true and every planet characteristics get display
            for(unsigned int i = 0; i<ThisSystem.size(); i++)
                ThisSystem[i].DisplayPlanet(NS.getMass());
    }
    cout << "\n\n" << endl;
    //printf("\nBeginning planetary implementation");


    NS.getAsteroidBelt().clear();
    NS.getSystem().clear();

    printf("Seed : %u\n", Rand);
    //system("PAUSE");

    return 0;
}


unsigned int InputSeed()
{   //ask user to input a seed
    unsigned int Seed = 0;

    while(true){
      printf("\nEnter Seed INT (positive) : ");
      scanf("%u", &Seed);

      if ((cin) && (Seed >= 0) && (Seed <= INT_MAX))
        break;

      cin.clear();
      cin.ignore( 1000, '\n' );
      printf("Seed invalid, program terminated\n");
      exit(-1);
    }
    return Seed;
}


/*  //will be used to get a precise RGB color of the star from which wavelength it radiates
    //not my function

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


