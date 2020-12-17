#include "Classes.h"
#include "PlanetFunctions.h"
#include <stdio.h>
#include <math.h>
#include <string>

#define EARTH_DENSITY 5.51
#define EARTH_YEAR 365.25636


float CompositionCoeff [10][2] = {  //constants to calculate mass radius approximation
    { 0.7965, 0.2549 }, //100% iron
    { 0.9412, 0.2646 }, //50% iron
    { 0.9860, 0.2677 }, //32.5% iron
    { 0.9969, 0.2682 }, //25% iron
    { 1.0073, 0.2690 }, //20 iron
    { 1.0496, 0.2719 }, //Mg/Si
    { 1.1657, 0.2695 }, //25% water / 52.5 MgSi / 22% iron
    { 1.2482, 0.2678 }, //45% water / 48,5% MgSi / 6.5% iron
    { 1.3892, 0.2661 }, //100% water
    { 1.8971, 0.4152 }, //100% Hydrogen
};

float ProbaRockyCompos[3][10] = {   //probability of composition apparition of rocky planets
    //I                  R          W  H
    {2, 10, 17, 22, 22, 17,  8,  1, 0, 0},
    {1, 11, 15, 30, 15,  7,  9,  7, 5, 0},
    {0,  4, 11, 14, 15, 17, 17, 13, 9, 0}
};

float CompositionByType[10][5] = {  //composition of planets for there types
    //Iron    R   W   He  Hy
    { 100,    0,  0,  0,  0 },
    {  50,   50,  0,  0,  0 },
    {32.5, 67.5,  0,  0,  0 },
    {  25,   75,  0,  0,  0 },
    {  20,   80,  0,  0,  0 },
    {   5,   95,  0,  0,  0 },
    {  22, 52.5, 25,  0,  0 },
    { 6.5, 48.5, 45,  0,  0 },
    {   1,    0, 99,  0,  0 },
    {   2,    0,  0, 95,  3 },
};



void Planet::SetRockyPlanetPhysical (float StarLum, float StarMass) {  
    //set rocky planet physical characteristics and  composition and temperature
    float *TypeProba = ProbaRockyCompos [Habitable];
    getHillSphereLimit (StarMass);
    int random = RandomInt (1, 100);
    int Buffer = 1;
    for (int i=0; i<10; i++)    {  
        //type of planet determination
        Buffer += TypeProba [i];
        if (random <= Buffer)
        {
            Buffer = i;
            break;
        }
    }

    Mass = RandomFloat (0.3, 1.75);
    if (RandomInt(1, 100) < 20 ) //could be a super earth
        Mass += RandomFloat (0.0, 15.0);

    switch (Buffer)
    {   //set the planet type
        case 0:
            Type = "Terrestrial pure iron planet      ";
            break;
        case 1:
            Type = "Terrestrial dense iron planet    ";
            break;
        case 2:
            Type = "Terrestrial iron/silicate planet ";
            break;
        case 3:
            Type = "Terrestrial iron/silicate planet ";
            break;
        case 4:
            Type = "Terrestrial iron/silicate planet ";
            break;
        case 5:
            Type = "Terrestrial iron/silicate planet ";
            break;
        case 6:
            Type = "Terrestrial ocean planet             ";
            break;
        case 7:
            Type = "Terrestrial dense ocean planet";
            break;
        case 8:
            Type = "Terrestrial pure water world    ";
            break;
        case 9:
            Type = "NOT A TERRESTRIAL PLANET";  //not suppose to be here but we never know
            break;
        default :
            printf("\nBROKEN BUFFER VALUE : %d", Buffer);
            break;
    }


    Radius = CompositionCoeff [Buffer][0] * pow ( Mass, CompositionCoeff [Buffer][1] ) + RandomFloat (-0.2, 0.2);

    Density = (float)Mass / pow ((float)Radius, 3.0) * (float)EARTH_DENSITY;
    Gravity = (float)Mass / pow ((float)Radius, 2.0); ;

    Composition = CompositionByType [Buffer];
    if (Buffer < 6) {
        //no water
        float ThisRandom = RandomFloat (-3.2, 3.2);
        int IndexToChange = RandomInt (0, 1);
        for (int i=0; i<100 || ! (Composition [IndexToChange] + ThisRandom >= 0 && Composition [IndexToChange] + ThisRandom <= 100) ; i++)
            ThisRandom = RandomFloat(-3.2, 3.2);

        Composition [IndexToChange] += ThisRandom;
        Composition [1-IndexToChange] -= ThisRandom;
    }
    else if (Buffer != 8)   {
        //not a water world
        float ThisRandom = RandomFloat (-4.2, 4.2);
        float OverallVariation = ThisRandom/RandomFloat (1.0, 2.0);
        int IndexToChange = RandomInt (0, 1);
        Composition [IndexToChange] += ThisRandom;
        Composition [1-IndexToChange] -= OverallVariation;
        Composition [2] -= OverallVariation;
    }
    else    {
        //water world
        float ThisRandom = RandomFloat (-3.2, 3.2);;
        int IndexToChange = RandomInt (0, 1);
        if (IndexToChange == 1)
            IndexToChange = 2;

        for (int i=0; i<100 || ! (Composition [IndexToChange] + ThisRandom >= 0 && Composition [IndexToChange] + ThisRandom <= 100) ; i++)
            ThisRandom = RandomFloat(-3.2, 3.2);

        Composition [IndexToChange] += ThisRandom;
        Composition [2-IndexToChange] -= ThisRandom;
    }



    Albedo = 0.0;
    GreenHouse = 20;
    minTemp = getMinTemperature (StarLum) - 273.15 ;
    maxTemp = getMaxTemperature (StarLum) - 273.15;
    //cout << "\nTmin Tmax " << minTemp << " " << maxTemp;

    if (Buffer > 5) {
        //set special albedo for water dominant planets
        if(maxTemp < -5.5)  {
            Albedo = 0.75;  //ice albedo
            GreenHouse = 20;
            Type = "Terrestrial ice world            ";
        }
        else if(maxTemp < 51.0) {
            Albedo = 0.32;  //ocean and clouds albedo
            GreenHouse = 50;
        }
        else if(maxTemp < 80.5) {
            Albedo = 0.73;   //rock, almost no water,albedo but big clouds
            GreenHouse = 110;
            Type = "Terrestrial cloudy world         ";
        }
        else    {
            Albedo = 0.85;  //rock, all water is gone
            GreenHouse = 400;

            //TODO : correct radius and mass change
            Radius *= (1 - ( Composition[2] / 100)) + 0.1;

            Type = "Terrestrial venus type world     ";
            Composition[0] += Composition[2]/2.0;
            Composition[1] += Composition[2]/2.0;
            Composition[2] = 0;
        }
        //cout << "\nAlbedo " << Albedo;
    }
    else    {
        //TODO set special albedo for any planet types
        GreenHouse = 53;
        Albedo = 0.29;
    }

    minTemp = getMinTemperature (StarLum);
    maxTemp = getMaxTemperature (StarLum);

    if(getHillSphereLimit(StarMass) < 0.005)    {
        //hill sphere very narrow
        MajorMoonNumber = 0;
        MinorMoonNumber = 0;
        //cout << "Too small to have a moon" << endl;
    }
    else    {
        //enough space for moons
        //TODO change this method with hill sphere and roche limit, and tidal locking
        MajorMoonNumber = RandomInt ( -1, (int)(Radius + 0.7) - 1)  + 1;
        MinorMoonNumber = RandomInt ( -1, (int)(Mass + 0.3) + 2)    + 1;
        for (int i=0; i<MajorMoonNumber; i++)   {
            Planet Moon;

            MajorMoons.push_back (Moon);
        }
        for (int i=0; i<MinorMoonNumber; i++)   {
            Planet Moon;

            MinorMoons.push_back (Moon);
        }
    }


    RingSystem = false;         //TODO : ring systemes ???????
};

void Planet::SetGasPlanetPhysical (float StarLum, float StarMass)
{   //set ice giant physical characteristics and  composition and temperature
    Mass = RandomFloat (10.5, 19.9);
    Albedo = 0.29;
    GreenHouse = 0;

    getHillSphereLimit (StarMass);
    Radius = 1.6545*pow (Mass, 0.3564) + RandomFloat (-0.2, 0.2);

    Density = (float)Mass / pow (Radius, 3.0) * EARTH_DENSITY;
    Gravity = (float)Mass / pow (Radius, 2.0);

    Type = "Ice giant";

    minTemp = getMinTemperature (StarLum);
    maxTemp = getMaxTemperature (StarLum);

    Composition = CompositionByType [9];
    if (getHillSphereLimit(StarMass) < 0.005)   {
        MajorMoonNumber = 0;
        MinorMoonNumber = 0;
        //cout << "Too small to have a moon" << endl;
    }
    else    {
        MajorMoonNumber = RandomInt (1, (int)(Radius/1.7 + 0.7)+1);
        MinorMoonNumber = RandomInt (3, (int)(  Mass/100 + 0.3)+1);
        for (int i=0; i<MajorMoonNumber; i++)   {
            Planet Moon;

            MajorMoons.push_back (Moon);
        }
        for (int i=0; i<MinorMoonNumber; i++)   {
            Planet Moon;

            MinorMoons.push_back    (Moon);
        }
    }

    RingSystem = true;  //TODO ring system parameters ??? (depending on moons and roche 
};

void Planet::SetGasGiantPhysical (float StarLum, float StarMass)
{   //set gas giant physical characteristics and  composition and temperature
    Mass = RandomFloat (10.0, 4500);   //at 4131 the giant collapse in a brown dwarf
    Albedo = 0.340;

    getHillSphereLimit (StarMass);

    if (Mass < 4131)    {
        //gas giant upper limit
        if (Mass >= 317.2)  {
            // >= jupiter mass --> electron degeneracy prevent the diameter to increase more
            Radius = 11.2 + RandomFloat (-0.2, 0.2);
            Type = "Jupiterian gas giant";
        }
        else    {
            if (RandomInt (0,10) < 2)   {
                Radius = RandomFloat (11.9, 21.28);  //radius from 1.1 to 1.9 the radius of jupiter
                Type = "Puffy giant";   //extremely low density jupiter
            }
            else    {
                Radius = 1.2635 * log (Mass) + 4.4921 + RandomFloat (-0.2, 0.2);
                Type = "Saturnian gas giant";
            }
        }
    }
    else    {
        //small brown dwarf
        Type = "Brown dwarf";
        float StarMass [2] = {4121, 24409};
        float StarRadi [2] = {11.2, 55.3};

        Mass =  RandomFloat (StarMass [0], StarMass [1]);
        Radius = RandomFloat ( StarRadi [0], StarRadi [1] );
        Temp = 1550 * pow (Mass/0.05, 0.83 );

        //setTemperature( 1550 * pow(getMass()/0.05, 0.83 ) );
        //setLuminosity( 0.00004 * pow(getMass()/0.05, 2.64 ) );
    }

    Gravity = Mass / pow (Radius, 2.0);
    Density = (float)Mass / pow (Radius, 3.0)* (float)EARTH_DENSITY;

    minTemp = getMinTemperature (StarLum);
    maxTemp = getMaxTemperature (StarLum);

    if (getHillSphereLimit(StarMass) < 0.005)   {
        MajorMoonNumber = 0;
        MinorMoonNumber = 0;
        //cout << "Too small to have a moon" << endl;
    }
    else    {
        MajorMoonNumber = RandomInt (1, (int)(Radius/1.7) + 1) + 1;

        if ((Mass/100 + 0.3) + 1 < 6 )
            MinorMoonNumber = RandomInt (5 , 9);
        else
            MinorMoonNumber = RandomInt (6 ,(int)(Mass/100 + 0.3) + 1);


        for (int i = 0; i < MajorMoonNumber; i++)   {
            Planet Moon;
            MajorMoons.push_back (Moon);
        }

        for (int i = 0; i < MinorMoonNumber; i++)   {
            Planet Moon;

            MinorMoons.push_back (Moon);
        }
    }

    RingSystem = true;
};



void Planet::setOrbitalValues (float InnerLimit, float OuterLimit, float StarMass)
{   //set planet orbit values
    do {
        eccentricity = RandomFloat (0.0, 0.078);
        Periabsis = SemiMajor * (1-eccentricity);
        Apoapsis  = SemiMajor * (1+eccentricity);
    } while (Periabsis < InnerLimit || Apoapsis > OuterLimit);

    OrbitalPeriod = sqrt ( pow(SemiMajor, 3.0)/ StarMass);
    Velocity = sqrt (StarMass / SemiMajor);
    Oinclination = RandomFloat (-2.0, 2.0);

    if (Oinclination == 0.0)    {
        LoAN = 0; AoP = -1;
    }
    else    {
        LoAN = RandomFloat (0.0, 360.0);
        AoP = RandomFloat (0.0, 180.0);
    }
};

void Planet::DisplayPlanet (float StarMass)
{   //display planet characteristics
    printf ("%s :", Type.c_str ());
    if (Habitable == 1)
        printf (" (in habitable z)");

    if (PlanetType == 2)
        printf ("\nMass : %.3f Jupiter (%.0f Earth), Radius : %.3f Earth radius", Mass/317.2, Mass ,Radius);
    else
        printf ("\nMass : %.2f Earth mass, Radius : %.3f Earth radius", Mass, Radius);

    if (PlanetType != 0)
        printf ("\nDensity : %.2f g/cm^3, Gravity : %.2f Earth, Escape V :%.2f Km/s", Density, Gravity, getEscapeVelocity ());
    else
        printf ("\nDensity : %.2f g/cm^3, Gravity : %.2f Earth gravity, Escape V :%.2f Km/s\nCompo : %.2f iron, %.2f MgSi, %.2f water", Density, Gravity, getEscapeVelocity (),Composition [0], Composition [1], Composition [2]);


    printf ("\n%d major moons, %d minor moon", MajorMoonNumber, MinorMoonNumber);
    printf ("\nOF : %.2f days (%.2f years), %.4f AU  hill sphere\nTemp: %d degres <----> %d degres", OrbitalPeriod*EARTH_YEAR, OrbitalPeriod, getHillSphereLimit (StarMass), (int) (minTemp - 273.15) , (int) (maxTemp - 273.15));
    //printf("\norbit %.3f AU <----> %.3f AU\n", Periabsis, Apoapsis);
    printf ("\nseed : %d", PlanetSeed);
    if (minTemp > -20.5 + 273.15 && maxTemp < 55 + 273.15)  {
        if(PlanetType != 0)
            printf  ("\n\nPOSSIBLE HABITABLE MOON YOUHOUUUUU\n");
        else    {
            if ( minTemp > 5 + 273.15 && maxTemp < 20 + 273.15 && Gravity > 0.7 && Gravity < 1.3 && eccentricity <= 0.2 )
                printf("\n\nHABITABLE Earth clone\n");
            else if (Gravity < 2 && Gravity > 0.4)
                printf("\n\nHmmmmmmm potential colony\n");
            else if ( Gravity >=  2)
                printf("\n\nHmmmmmmm survivable but gravity too strong\n");
            else if ( Gravity <=  0.4)
                printf("\n\nHmmmmmmm survivable but gravity too low\n");
        }
    }
    cout << "\n\n" << endl;
}


