#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string>

#include "PlanetFunctions.h"
#include "StarFunctions.h"
#define SUN_TEMP 5766
#define PI 3.141592653
#define SUN_RADIUS_KM 696392
#define SUN_RADIUS_AU 0.00465047
#define SUN_DENSITY 1.408
#define EARTH_RADIUS 6371

using namespace std;
//typedef map<char, float*> StarClass;
//typedef pair<char, float*> PairClass;

enum {O0, I, II, III, IV, V};
enum {O, B, A, F, G, K, M, D, INDETERMINE, FD, BD};


float StarVClass[7][2] =
{   //Main class : dwarf star
        // Lmin, Lmax
  /*O*/  {20000, 800000},
  /*B*/  {80, 20000},
  /*A*/  {6.5 , 80},
  /*F*/  {1.26 , 6.5 },
  /*G*/  {0.42 , 1.26 },
  /*K*/  {0.072 , 0.42 },
  /*M*/  {0.000015 , 0.072 }
};
float StarIVClass[7][2] =
{   //Sub giant star
        // Lmin, Lmax
  /*O*/  {80000, 100000},
  /*B*/  {102, 34000},
  /*A*/  {13 , 102},
  /*F*/  {9 , 13 },
  /*G*/  {8 , 9 },
  /*K*/  {8 , 9 },
  /*M*/  {9 , 10}
};
float StarIIIClass[7][2] =
{   //Giant star
        // Lmin, Lmax
  /*O*/  {500000, 300000},
  /*B*/  {170, 500000},
  /*A*/  {97 , 170},
  /*F*/  {95 , 97 },
  /*G*/  {95 , 96 },
  /*K*/  {96 , 98 },
  /*M*/  {98 , 105 }
};
float StarIIClass[7][2] =
{   //Bright giant star
        // Lmin, Lmax
  /*O*/  {40000, 52000},
  /*B*/  {4000, 40000},
  /*A*/  {2000 , 4000},
  /*F*/  {960 , 2000 },
  /*G*/  {950 , 960 },
  /*K*/  {950 , 1000 },
  /*M*/  {1000 , 8000 }
};
float StarIClass[7][2] =
{   //Super giant star
        // Lmin, Lmax
  /*O*/  {10000, 1500000},
  /*B*/  {10000, 1500000},
  /*A*/  {1000 , 100000},
  /*F*/  {1000 , 100000 },
  /*G*/  {20000 , 500000 },
  /*K*/  {20000 , 500000 },
  /*M*/  {20000 , 500000 }
};
float Star0Class[7][2] =
{   //hyper giant star
        // Lmin, Lmax
  /*O*/  {1000000, 5000000},
  /*B*/  {380000, 2000000},
  /*A*/  {300000, 600000 },
  /*F*/  {300000, 600000 },
  /*G*/  {100000, 500000 },
  /*K*/  {100000, 500000 },
  /*M*/  {86000 , 500000 }
};
float StarDClass[7][2] =
{   //white dwarf
  /*O*/  {0.2, 1},
  /*B*/  {0.06, 0.2},
  /*A*/  {0.0006 , 0.06},
  /*F*/  {0.0002 , 0.0006 },
  /*G*/  {0.00009 , 0.0002 },
  /*K*/  {0.00008 , 0.00009 },
  /*M*/  {0.00005 , 0.00008 }
};

float TempertureScaleMinmax[9][3] =
{       //Tmax,  Tmin, coeff
  /*O*/  {54000,  33200, 2400},
  /*B*/  {29700, 10700, 2111},
  /*A*/  {9790,   7323, 274},
  /*F*/  {7300,   6033, 141},
  /*G*/  {5940,   5335, 67},
  /*K*/  {5150,   3880, 141},
  /*M*/  {3840,   2376, 165},
  /*D*/  {40000, 4000, 8000},
  /*Un*/ {0, 0, 0}
};


void CreateMultipleStarSystem( Star *CenterOfMass)
{
    CenterOfMass->Companions = vector<Star>();
    float separation;

    Star Companion1;
    CreateStar(&Companion1);

    Star Companion2;
    CreateStar(&Companion2);

    if(Companion1.getMass() < Companion2.getMass())
    {
       Star Tempo = Companion1;
       Companion1 = Companion2;
       Companion2 = Tempo;
    }


    int RandChoice = RandomInt(0,8);

    if( RandChoice < 4)  //close companions
    {
        CenterOfMass->setClass("Close binary system");
        CenterOfMass->setClassInt(0);
        separation = RandomFloat(0.2 + Companion1.getRadius()*SUN_RADIUS_AU*4 + Companion2.getRadius()*SUN_RADIUS_AU, 6.0);  //AU
        Companion1.eccentricity = RandomFloat(0.4, 0.7);
        Companion2.eccentricity = RandomFloat(0.4, 0.7);
    }
    else    //distant companions
    {
        CenterOfMass->setClass("Distant binary system");
        CenterOfMass->setClassInt(1);
        separation = RandomFloat(120 + Companion1.getRadius()*SUN_RADIUS_AU + Companion2.getRadius()*SUN_RADIUS_AU, 600.0);  //AU
        Companion1.eccentricity = RandomFloat(0.4, 0.7);
        Companion2.eccentricity = RandomFloat(0.4, 0.7);
    }

        CenterOfMass->setMass( Companion1.getMass() + Companion2.getMass());

        Companion1.SemiMajor = separation * (Companion2.getMass() / CenterOfMass->getMass());
        Companion1.apoabsis = (1+Companion1.eccentricity) * Companion1.SemiMajor;
        Companion1.periabsis= (1-Companion1.eccentricity) * Companion1.SemiMajor;

        Companion2.SemiMajor = separation * (Companion1.getMass() / CenterOfMass->getMass());
        Companion2.apoabsis = (1+Companion2.eccentricity) * Companion2.SemiMajor;
        Companion2.periabsis= (1-Companion2.eccentricity) * Companion2.SemiMajor;


        float MinT = Companion2.periabsis + Companion1.periabsis;
        float MaxT = Companion2.apoabsis + Companion1.apoabsis;

        CenterOfMass->setRocheLimit(MaxT*2);
        CenterOfMass->setLuminosity(Companion1.getLuminosity()+Companion2.getLuminosity());
        CenterOfMass->setRadius(MinT);


        if( RandChoice < 4)  //close companions
        {
            PopulatePlanets(CenterOfMass);
        }
        else    //distant companions
        {
            Companion1.OuterEdge = Companion1.getHillSphere(Companion2.getMass());
            Companion2.OuterEdge = Companion2.getHillSphere(Companion1.getMass());
            if(Companion1.OuterEdge < Companion2.OuterEdge)
            {
                float tempo = Companion1.OuterEdge;
                Companion1.OuterEdge = Companion2.OuterEdge;
                Companion2.OuterEdge = tempo;
            }
            PopulatePlanets(&Companion1);
            PopulatePlanets(&Companion2);
        }

        if( RandChoice < 4 &&  (MinT <= 0.1 || (MinT <= Companion1.getRadius()*SUN_RADIUS_AU+Companion2.getRadius()*SUN_RADIUS_AU ) ) )
            cout << "CHIER C TROP SERRE " << MinT << " " << Companion1.getRadius()*SUN_RADIUS_AU+Companion2.getRadius()*SUN_RADIUS_AU;
        else if( RandChoice >= 4 && MinT <= Companion1.getOuterLimit() + Companion2.getOuterLimit())
            cout << "CHIER C TROP SERRE " << MinT << " " << Companion1.getOuterLimit()+Companion2.getOuterLimit();



        CenterOfMass->Companions.push_back(Companion1);
        CenterOfMass->Companions.push_back(Companion2);

}

void CreateStar(Star *NewStar)
{   //create a star from scratch
    char StarDeterType[9] = {'O', 'B', 'A', 'F', 'G', 'K', 'M', 'D', '?'};
    string StarDeterClass[6] = {"0", "I", "II", "III", "IV", "V"};

    int StarType = DetermineStarType();     //type of the star : O, B, A, ...
    //StarType = 1;

    int StarClass = DeterminStarClass(StarType);    //class of the star : 0, I, II, ...
    //NewStar.setClass(StarDeterClass2[StarClass].c_str());

    int TemperatureClass = getTemperatureClassification();  //0 to 9
    //NewStar.setLuminosityClass(TemperatureClass);

    if(StarType == O && StarClass == V && TemperatureClass < 5)
        TemperatureClass = 5;
    else if(StarType == M && TemperatureClass > 6)
        TemperatureClass = 6;

    unsigned int StarTemp = getStarTemperature(StarType, TemperatureClass);

    float Luminosity = getStarLuminosity(StarType, StarClass);

    if(StarType == D)
    {   //white dwarf, faint white dwarf or black dwarf
        NewStar->setType('D');
        float Mass = RandomFloat(0.17, 1.44);
        NewStar->setMass(Mass);
        NewStar->setRadius( pow(Mass, (float)-1/3));    //Radius in EarthRadius !!!
        if(RandomInt(0,5) == 1)
        {   //faint or black
            if(RandomInt(0, 20) <= 1)   //black
            {
                StarType = BD;
                Luminosity = 0.00000001;
                StarTemp = 10;
            }
            else    //faint
            {
                StarType = FD;
                Luminosity = 0.004;
                StarTemp = 1200;
            }
        }
    }
    else if(StarType != INDETERMINE)
    {   //all casual stars
        NewStar->setType(StarDeterType[StarType]);
        NewStar->setMass(guessStarMassWithLum(Luminosity));
        float StarRad = StarRadius(StarTemp, Luminosity);
        NewStar->setRadius(StarRad);
    }

    NewStar->setClassInt(StarClass);
    NewStar->setTypeInt(StarType);


    NewStar->setLuminosity(Luminosity);
    NewStar->setLuminosityClass(TemperatureClass);
    NewStar->setClass(StarDeterClass[StarClass]);
    NewStar->setTemperature(StarTemp);

    if(StarType == INDETERMINE) //special stars
    {   //special star (Brown dwarf, neutron star, black hole, wolf rayet, pulsar, Carbon star, ...
        string SpeStar[5] = {      "Brown dwarf",    "Neutron star", "Black hole", "Wolf Rayet star", "Pulsar"};
        float StarMass[5][2] = { {0.012412, 0.075318}, {0.2, 2.9},    {3, 500},       {10, 19},     {0.17, 2.9}};
        float StarRadi[5][2] = {   {0.1005, 0.431},{0.0000143, 0.0000172},   {0.1, 0.1},    {0.6, 6.6},    {0.0000143, 0.0000172}};
        float StarTemp[5][2] = {   {300.0, 2800.0},    {1.1, 2.9}, {0.001, 0.2},  {44000, 200000}, {0.17, 2.9}};
        float StarLum [5][2] = {   {300.0, 2800.0},    {1.1, 2.9},  {0.0, 0.0},  {160000, 500000},    {0.17, 2.9}};

        int ChooseStar = RandomInt(0, 4);

        NewStar->setClass(SpeStar[ChooseStar]);

        NewStar->setMass( RandomFloat(StarMass[ChooseStar][0], StarMass[ChooseStar][1]) );
        NewStar->setTemperature( RandomFloat(StarTemp[ChooseStar][1], StarTemp[ChooseStar][1]) );
        NewStar->setRadius( RandomFloat( StarRadi[ChooseStar][0], StarRadi[ChooseStar][1] ) );
        NewStar->setLuminosity( RandomFloat( StarLum[ChooseStar][0], StarLum[ChooseStar][1] ) );
        NewStar->setDensity((float) NewStar->getMass()/(pow(NewStar->getRadius()*SUN_RADIUS_KM, 3.0) / pow(SUN_RADIUS_KM, 3.0)));

        if(ChooseStar == 0)
        {   //brown dwarf
            NewStar->setTemperature( 1550 * pow(NewStar->getMass()/0.05, 0.83 ) );
            NewStar->setLuminosity( 0.00004 * pow(NewStar->getMass()/0.05, 2.64 ) );
        }
        else if(ChooseStar == 1)
        {   //neutron star
            //NewStar.setRadius( pow(NewStar.getMass(), (float)-1/3));
            NewStar->setTemperature(getStarTemperature(D, 1));
            NewStar->setDensity((float) NewStar->getMass()/(pow(NewStar->getRadius()*SUN_RADIUS_KM/EARTH_RADIUS, 3.0) / pow(EARTH_RADIUS, 3.0)));
        }
        else if(ChooseStar == 4)    //pulsar
        {
            //NewStar.setRadius( 0.001881420346934 );
            NewStar->setTemperature( getStarTemperature(D, 1) );
            NewStar->setDensity((float) NewStar->getMass()/(pow(NewStar->getRadius()*SUN_RADIUS_KM/EARTH_RADIUS, 3.0) / pow(EARTH_RADIUS, 3.0)));
        }

    }

    NewStar->setVolume( (4.0/3.0)*PI* (pow(NewStar->getRadius(), 3.0 ) ));
    if(NewStar->getTypeInt() == D || NewStar->getTypeInt() == FD || NewStar->getTypeInt() == BD)
        NewStar->setDensity((float) NewStar->getMass()/(pow(NewStar->getRadius()*SUN_RADIUS_KM/EARTH_RADIUS, 3.0) / pow(EARTH_RADIUS, 3.0)));
    else if(NewStar->getTypeInt() != INDETERMINE)
        NewStar->setDensity((float) NewStar->getMass()/(pow(NewStar->getRadius()*SUN_RADIUS_KM, 3.0) / pow(SUN_RADIUS_KM, 3.0)));
}

void DisplayStarCarac(Star NS)
{   //display the star physical characteristics
    string StarDeterTypeColor[12] = {"blue", "blue-white", "white", "white-yellow", "yellow", "orange", "red", "white dwarf", "????", "faint white dwarf", "black dwarf"};
    string StarDeterClass[6] = {"hypergiant", "supergiant", "brightgiant", "giant", "subgiant", "dwarf main class"};

    cout << endl;
    if(NS.getTypeInt() == INDETERMINE)
        printf("%s\n", NS.getClass().c_str());
    else
    {
        printf("%c%d %s  ",NS.getType(), NS.getLuminosityClass(), NS.getClass().c_str());
        if(NS.getType() == 'D') //white dwarf
            printf("%s\n", StarDeterTypeColor[NS.getTypeInt()].c_str());
        else
            printf("%s %s\n", StarDeterTypeColor[NS.getTypeInt()].c_str(), StarDeterClass[NS.getClassInt()].c_str() );
    }

    printf("Temperature : %.0f K\nRadius : %.5f AU (%.3f sun percent)\nLuminosity : %f Solar luminosity\n", ((float)NS.getTemperature()), NS.getRadius()*SUN_RADIUS_AU, NS.getRadius(), NS.getLuminosity());
    if(NS.getDensity() >= 0 && NS.getDensity() < 10000000)
        printf("Mass : %.3f solar mass, Density : %.3f g/cm^3\n", NS.getMass(), NS.getDensity());
    else
        printf("Mass : %.3f solar mass, Density : > 1 billion g/m^3\n", NS.getMass());

    //printf("\nRoche zone : %f\nFrost line : %f\nOuter limit : %f", NS.getRocheLimit(), NS.getFrostZone(), NS.getOuterLimit());
    if(NS.eccentricity != 0)
        printf("\necc %.4f, Semimajor %.4f, Apo %.4f, Peri %.4f", NS.eccentricity, NS.SemiMajor, NS.apoabsis, NS.periabsis);
    printf("\nHabitable zone from %.3f to %.3f\n", NS.getHabitableZoneInf(), NS.getHabitableZoneSup());
}

void DisplayDoubleStar(Star DoubleStarCenter, bool DispPlanetCharac)
{
    printf("\n%s\n", DoubleStarCenter.getClass().c_str());

    if(DoubleStarCenter.getClassInt() == 0)
    {
        DisplayStarCarac(DoubleStarCenter.Companions[0]);
        cout << endl;
        DisplayStarCarac(DoubleStarCenter.Companions[1]);
        DisplaySystemsCaracteristics(DoubleStarCenter);   //display the system
        cout << "\n" <<endl;
        vector<Planet> ThisSystem = DoubleStarCenter.getSystem();
        if(DispPlanetCharac)
            for(unsigned int i = 0; i<ThisSystem.size(); i++)
                ThisSystem[i].DisplayPlanet(DoubleStarCenter.getMass());
    }
    else
    {
        DisplayStarCarac(DoubleStarCenter.Companions[0]);
        DisplaySystemsCaracteristics(DoubleStarCenter.Companions[0]);   //display the system
        cout << "\n" <<endl;
        vector<Planet> ThisSystem = DoubleStarCenter.Companions[0].getSystem();
        if(DispPlanetCharac)
            for(unsigned int i = 0; i<ThisSystem.size(); i++)
                ThisSystem[i].DisplayPlanet(DoubleStarCenter.Companions[0].getMass());

        cout << "\n" <<endl;
        DisplayStarCarac(DoubleStarCenter.Companions[1]);
        DisplaySystemsCaracteristics(DoubleStarCenter.Companions[1]);   //display the system

        cout << "\n" <<endl;
        ThisSystem = DoubleStarCenter.Companions[1].getSystem();
        if(DispPlanetCharac)
            for(unsigned int i = 0; i<ThisSystem.size(); i++)
                ThisSystem[i].DisplayPlanet(DoubleStarCenter.Companions[1].getMass());
    }
}



float getStarLuminosity(int StarType, int StarClass)    //correction à donner
{   //get some random luminosity
    if(StarType == D)
    {
        return RandomFloat(0.00005, 1);
    }
    else if(StarType >= 7)
    {
        //printf("\nNo star class yet for %d", StarType);
        return 0;
    }

    switch(StarClass)
    {
    case O0:
        return (float)RandomInt(Star0Class[StarType][0], Star0Class[StarType][1]);
        break;
    case I:
        return (float)RandomInt(StarIClass[StarType][0], StarIClass[StarType][1]);
        break;
    case II:
        return RandomFloat(StarIIClass[StarType][0], StarIIClass[StarType][1]);
        break;
    case III:
        return RandomFloat(StarIIIClass[StarType][0], StarIIIClass[StarType][1]);
        break;
    case IV:
        return RandomFloat(StarIVClass[StarType][0], StarIVClass[StarType][1]);
        break;
    case V:
        return RandomFloat(StarVClass[StarType][0], StarVClass[StarType][1]);
        break;
    default:
        printf("No star class for %d\n", StarClass);
        exit(0);
        break;
    }
    return 0;
}

int DeterminStarClass(int StarType)
{   //class of the star : 0, I, II, ...
    int ClassProba = RandomInt(0, 600); //should be 0-1000
    int StarClassInt = 0;
    if(ClassProba <= 2 && StarType != O)
    {   //hyper giant star 0,1
        StarClassInt = O0;
    }
    else if(ClassProba <= 10)
    {   //Super giant star 1
        StarClassInt = I;
    }
    else if(ClassProba <= 60)
    {   //Bright giant star 5
        StarClassInt = II;
    }
    else if(ClassProba <= 190)
    {   //Giant star 13
        StarClassInt = III;
    }
    else if(ClassProba <= 200 && StarType != M)
    {   //Sub giant star 10
        StarClassInt = IV;
    }
    else
    {   //Main class star 65,9
        StarClassInt = V;
    }
    return StarClassInt;
}

int DetermineStarType()
{   //type of the star : O, B, A, ....
    int ClassProba = RandomInt(1, 1000);
    int StarType;
    if(ClassProba <= 2)
    {   //type O (proba 0.2)
        StarType = O;
    }
    else if(ClassProba <= 4)
    {   //type B (proba 0.2)
        StarType = B;
    }
    else if(ClassProba <= 11)
    {   //type A (proba 0.7)
        StarType = A;
    }
    else if(ClassProba <= 13)
    {   //type F (proba 2)
        StarType = F;
    }
    else if(ClassProba <= 68)
    {   //Type G (proba 3.5) (here 5.5)
        StarType = G;
    }
    else if(ClassProba <= 148)
    {   //Type K (proba 8)
        StarType = K;
    }
    else if(ClassProba <= 198)
    {   //Type D (proba 5)
        StarType = D;
    }
    else if(ClassProba <= 900)
    {   //Type M (proba 80)
        StarType = M;
    }
    else
    {   //L, T, Y, W, C, S
        StarType = INDETERMINE;
    }
    return StarType;
}

unsigned int getStarTemperature(int StarType, int StarLuminosityClassif)
{   //return star temperature in Kelvin
    int Temp = TempertureScaleMinmax[StarType][1] + (TempertureScaleMinmax[StarType][2] * (9-StarLuminosityClassif));
    if(StarType == INDETERMINE)
        return Temp;

    if(StarLuminosityClassif == 0)
        Temp += RandomInt((int)-TempertureScaleMinmax[StarType][2]/6, (int)TempertureScaleMinmax[StarType][2]/6);
    else
        Temp += RandomInt((int)-TempertureScaleMinmax[StarType][2]/2, (int)TempertureScaleMinmax[StarType][2]/2);
    return Temp;
}

float StarLuminosity(float Radius, unsigned int TemperatureK)
{   //return the star luminosity in function of the luminosity of the sun
    return pow(Radius, 2)*pow( ((float)TemperatureK/SUN_TEMP), 4 );
}

float StarRadius(unsigned int TemperatureK, float StarLuminosity)
{   //return star radius in function of the size of the sun
    return sqrt((float)StarLuminosity / pow(((float)TemperatureK/SUN_TEMP), 4));
}

int getTemperatureClassification()
{  //luminosity number between 0 and 9
    return RandomInt(0,9);   //get percentage
}

int RandomInt(int a, int b){
    return rand()%((b - a) + 1) + a;
}

float mapValueX(float x, float in_min, float in_max, float out_min, float out_max)
{   //map the value of x (between in_min and in_max) between out_min and out_max
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void spectral_color(double &r,double &g,double &b,double l)
{ // RGB <0,1> <- lambda l <400,700> [nm]
    double t;  r=0.0; g=0.0; b=0.0;

    //Red
    if ((l>=400.0)&&(l<410.0)) {
        t=(l-400.0)/(410.0-400.0);
        r=    +(0.33*t)-(0.20*t*t);
    }
    else if ((l>=410.0)&&(l<475.0)) {
        t=(l-410.0)/(475.0-410.0);
        r=0.14         -(0.13*t*t);
    }
    else if ((l>=545.0)&&(l<595.0)){
        t=(l-545.0)/(595.0-545.0);
        r=    +(1.98*t)-(     t*t);
    }
    else if ((l>=595.0)&&(l<650.0)){
        t=(l-595.0)/(650.0-595.0);
        r=0.98+(0.06*t)-(0.40*t*t);
    }
    else if ((l>=650.0)&&(l<700.0)){
        t=(l-650.0)/(700.0-650.0);
        r=0.65-(0.84*t)+(0.20*t*t);
    }

    //Green
    if ((l>=415.0)&&(l<475.0)){
        t=(l-415.0)/(475.0-415.0);
        g=             +(0.80*t*t);
    }
    else if ((l>=475.0)&&(l<590.0)){
        t=(l-475.0)/(590.0-475.0);
        g=0.8 +(0.76*t)-(0.80*t*t);
    }
    else if ((l>=585.0)&&(l<639.0)){
        t=(l-585.0)/(639.0-585.0);
        g=0.84-(0.84*t)           ;
    }

    //Blue
    if ((l>=400.0)&&(l<475.0)){
        t=(l-400.0)/(475.0-400.0);
        b=    +(2.20*t)-(1.50*t*t);
    }
    else if ((l>=475.0)&&(l<560.0)){
        t=(l-475.0)/(560.0-475.0);
        b=0.7 -(     t)+(0.30*t*t);
    }
}

float guessStarMassWithTemp(unsigned int Temperature)
{   //guess a star mass with its temperature (class V)
    return (float)pow((float)Temperature/SUN_TEMP, (float)(1.0/0.505));
}

float guessStarMassWithLum(float Lum)
{   //guess a star Luminosity with its mass (Class V)
    if(Lum < 0.03418801)
        return pow(Lum, (float)1/2.3);
    if(Lum < 16.97056275)
        return pow(Lum, (float)1/4);
    if(Lum < 64000)
        return pow(Lum/1.5, (float)1/3.5);
    if(Lum <= 160000)
        return pow(Lum/3200, (float)1);
    if(Lum > 160000)
        return pow(Lum/3200, (float)1/1.25);
    return 0.0;
}

float RandomFloat(float a, float b){
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
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


