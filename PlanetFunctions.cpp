#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "PlanetFunctions.h"
#include "StarFunctions.h"

#define DEBUG false

using namespace std;

vector<Planet> CreatePlacePlanetsOnSSMeth1(Star ThisStar, int MaxPlanetNumber)
{   //place new planets in star system with at least one gaze giant planet
    if(DEBUG)
        printf("\ncreate using From The Giant method\n");
    vector<Planet> StarSystem;
    if(ThisStar.getMass() <= 0)
        return StarSystem;

    float DistOfMostMassiveGas = ThisStar.getFrostZone() + RandomFloat(0.1, 1.0);
    if(DistOfMostMassiveGas <= ThisStar.getRocheLimit() || DistOfMostMassiveGas >= ThisStar.getOuterLimit())
        return StarSystem;

    Planet GazGiant;
    GazGiant.Habitable = IsHabitable(DistOfMostMassiveGas, ThisStar.getHabitableZoneInf(), ThisStar.getHabitableZoneSup());
    GazGiant.setOrbitalRadius(DistOfMostMassiveGas);
    GazGiant.setPlanetType(2);
    StarSystem.push_back(GazGiant);

    //before frost line
    float DistFromStar = DistOfMostMassiveGas;
    while(MaxPlanetNumber > 0)
    {
        DistFromStar = DistFromStar / RandomFloat(1.4, 2.0);
        if(DistFromStar <= ThisStar.getRocheLimit())
            break;  //planet too close to the star to exist
        MaxPlanetNumber--;
        Planet NewPlan;

        NewPlan.Habitable = IsHabitable(DistFromStar, ThisStar.getHabitableZoneInf(), ThisStar.getHabitableZoneSup());
        NewPlan.setPlanetType(GasOrRock(DistFromStar, ThisStar.getFrostZone()));
        if(DistFromStar < DistOfMostMassiveGas && NewPlan.getPlanetType() != 0)
            NewPlan.setPlanetType(2);

        NewPlan.setOrbitalRadius(DistFromStar);
        StarSystem.push_back(NewPlan);
    }

    //after frost line and gas giant
    DistFromStar = DistOfMostMassiveGas;
    while(MaxPlanetNumber > 0) {
        DistFromStar = DistFromStar * RandomFloat(1.4, 2.0);
        if(DistFromStar >= ThisStar.getOuterLimit())
            break;  //planet too far to the star to exist
        MaxPlanetNumber--;

        Planet NewPlan;
        NewPlan.setPlanetType(GasOrRock(DistFromStar, ThisStar.getFrostZone()));

        NewPlan.setOrbitalRadius(DistFromStar);
        StarSystem.push_back(NewPlan);
    }

    OrderPlanetsByDistance(&StarSystem);
    return StarSystem;
}

vector<Planet> CreatePlacePlanetsOnSSMeth2(Star ThisStar, int MaxPlanetNumber)
{   //place planets from the center
    if(DEBUG)
        printf("\nCreate using From The center method\n");
    vector<Planet> StarSystem;
    if(ThisStar.getMass() <= 0)
        return StarSystem;

    float DistFirstPlan = ThisStar.getRocheLimit() + RandomFloat(0.1, 0.5);
    if(DistFirstPlan > ThisStar.getOuterLimit() || DistFirstPlan==0)
        return StarSystem;

    Planet FirstPlanet;
    FirstPlanet.setOrbitalRadius(DistFirstPlan);
    if(RandomInt(0,50) == 1)
        FirstPlanet.setPlanetType(1);
    else
        FirstPlanet.setPlanetType(0);
    FirstPlanet.Habitable = IsHabitable(DistFirstPlan, ThisStar.getHabitableZoneInf(), ThisStar.getHabitableZoneSup());
    StarSystem.push_back(FirstPlanet);

    while(MaxPlanetNumber > 0)
    {
        DistFirstPlan = DistFirstPlan * RandomFloat(1.4, 2.0);
        if(DistFirstPlan > ThisStar.getOuterLimit())
            break;

        MaxPlanetNumber--;
        Planet NewPlanet;

        NewPlanet.Habitable = IsHabitable(DistFirstPlan, ThisStar.getHabitableZoneInf(), ThisStar.getHabitableZoneSup());

        NewPlanet.setOrbitalRadius(DistFirstPlan);
        NewPlanet.setPlanetType(GasOrRock(DistFirstPlan, ThisStar.getFrostZone()));
        StarSystem.push_back(NewPlanet);
    }
    return StarSystem;
}

vector<Planet> CreatePlacePlanetsOnSSMeth3(Star ThisStar, int MaxPlanetNumber)
{   //place planets using Titus-Bode
    if(DEBUG)
        printf("\nCreate using Titus-Bode relation\n");
    vector<Planet> StarSystem;

    if(ThisStar.getMass() <= 0)
        return StarSystem;

    float Is = ThisStar.getRocheLimit();
    float Os = ThisStar.getOuterLimit();
    float FZ = ThisStar.getFrostZone();

    for(int i=0; i<MaxPlanetNumber; i++)
    {
        float ThisPlanetOrbit = (Is + (Is/4.0 * pow(2.0, (float)i))) + ( log((float)i+1.0)/10.0 );
        if(ThisPlanetOrbit > Os)
            break;

        Planet NewPlanet;

        NewPlanet.Habitable = IsHabitable(ThisPlanetOrbit, ThisStar.getHabitableZoneInf(), ThisStar.getHabitableZoneSup());

        NewPlanet.setOrbitalRadius(ThisPlanetOrbit);
        NewPlanet.setPlanetType(GasOrRock(ThisPlanetOrbit, FZ));

        StarSystem.push_back(NewPlanet);
    }

    return StarSystem;
}

vector<Planet> CreatePlacePlanetsOnSSMeth4(Star ThisStar, int MaxPlanetNumber)
{   //place planets with Benfords law
    if(DEBUG)
        printf("\nCreate using Benfords law\n");
    vector<Planet> StarSystem;
    float RefValues1[8] = {1.109, 1.137, 1.155, 1.179, 1.228, 1.289, 1.408, 1.710};

    /*for(int i=0; i<8; i++)
        RefValues1[i] += RandomFloat(0.091, 0.095);*/

    float RefValues2[16];
    for(int i=0; i<16; i++)
    {
        if(i<8)
            RefValues2[i] = RefValues1[i] + RandomFloat(0.091, 0.095);
        if(i>=8)
            RefValues2[i] = RefValues1[i-8] + RandomFloat(0.01, 0.03);
    }

    float FirstOrb = ThisStar.getRocheLimit() + 0.046;
    if(FirstOrb > ThisStar.getOuterLimit())
        return StarSystem;

    Planet FirstPlan;

    FirstPlan.Habitable = IsHabitable(FirstOrb, ThisStar.getHabitableZoneInf(), ThisStar.getHabitableZoneSup());
    FirstPlan.setOrbitalRadius(FirstOrb);
    FirstPlan.setPlanetType(GasOrRock(FirstOrb, ThisStar.getFrostZone()));


    for(int i=1; i<16; i++)
    {
        FirstOrb *= RefValues2[i];
        if(FirstOrb > ThisStar.getOuterLimit())
            break;
        Planet OtherPlanet;

        OtherPlanet.Habitable = IsHabitable(FirstOrb, ThisStar.getHabitableZoneInf(), ThisStar.getHabitableZoneSup());
        OtherPlanet.setOrbitalRadius(FirstOrb);
        OtherPlanet.setPlanetType(GasOrRock(FirstOrb, ThisStar.getFrostZone()));
        StarSystem.push_back(OtherPlanet);

        MaxPlanetNumber--;
        if(MaxPlanetNumber <= 0)
            break;
    }

    return StarSystem;
}


void PopulatePlanets(Star *NS)
{   //populate planets for the star NS

    //TODO : CORRECT PLANET PROPABILITY

    int MaxPlanets = (int) (NS->getOuterLimit()*2) %((int)(15+NS->getMass()*10.0));
    //cout << MaxPlanets << " " << ((int)(15+NS->getMass()*10.0)) << endl;
    int GenerationMethod = RandomInt(1,10);


    if(GenerationMethod <= 5)   //choose a generation system
        NS->setSystem(CreatePlacePlanetsOnSSMeth1(*NS, RandomInt(0,MaxPlanets)) );
    else if(GenerationMethod <= 7)
        NS->setSystem(CreatePlacePlanetsOnSSMeth2(*NS, RandomInt(0,MaxPlanets)) );
    else if(GenerationMethod <= 8)
        NS->setSystem(CreatePlacePlanetsOnSSMeth3(*NS, RandomInt(0,MaxPlanets)) );
    else
        NS->setSystem(CreatePlacePlanetsOnSSMeth4(*NS, RandomInt(0,MaxPlanets)) );

    //printf("\n%d planets created\n", NS.getSystem().size());
    setPlanets(NS);   //set all planets orbits characteristics


    NS->setAsteroidBelt(PlaceAsteroidBelts(*NS)); //place asteroid belts
}

void DisplaySystemsCaracteristics(Star ThisStar)
{
    cout << endl;
    bool DepFrost = false;
    bool inHab = false;
    vector<Planet> SSystem = ThisStar.getSystem();
    vector<AsteroidBelt> ABelts = ThisStar.getAsteroidBelt();

    printf("%d planets, %d asteroid fields\n\n", SSystem.size(), ABelts.size());

    int AstBelt = 0;
    if(ABelts.size()>0)
        AstBelt=ABelts.size();

    printf("\n-------Inner  limit-------      %.3f AU", ThisStar.getRocheLimit());
    for(unsigned int i=0; i<SSystem.size(); i++)
    {
        if( !inHab && SSystem[i].getOrbitalDistance() > ThisStar.getHabitableZoneInf() && SSystem[i].getOrbitalDistance() < ThisStar.getHabitableZoneSup())
        {
            printf("\n\n------Habitable zone------      %.3f AU", ThisStar.getHabitableZoneInf());
            inHab = true;
        }
        else if( inHab && SSystem[i].getOrbitalDistance() > ThisStar.getHabitableZoneSup())
        {
            printf("\n------Habitable zone------      %.3f AU\n", ThisStar.getHabitableZoneSup());
            inHab = false;
        }
        if( !DepFrost && SSystem[i].getOrbitalDistance() > ThisStar.getFrostZone() )
        {
            DepFrost = true;
            printf("\n\n-------Frost   Line-------      %.3f AU", ThisStar.getFrostZone());
        }

        if(AstBelt > 0)
        {   //possibly display asteroid belt
            if(SSystem[i].getOrbitalDistance() > ABelts[ABelts.size()-AstBelt].getInnerEdge())
            {
                DisplayAsteroidBelt(ABelts[ABelts.size()-AstBelt]);
                AstBelt--;
            }
        }

        printf("\n%s %d : %.3f AU",SSystem[i].getType().c_str() , i+1, SSystem[i].getOrbitalDistance());
        if(SSystem[i].eccentricity <= 0.2 && SSystem[i].getMinTemperature(ThisStar.getLuminosity()) > -20.5+273.15 && SSystem[i].getMaxTemperature(ThisStar.getLuminosity())  < 55+273.15)
        {
            if(SSystem[i].getPlanetType() != 0)
                printf("      \t\tPOSSIBLE HABITABLE MOON");
            else
                printf("      \tPOSSIBLE HABITABLE");
        }
    }

    if(inHab)
        printf("\n------Habitable zone------      %.3f AU\n", ThisStar.getHabitableZoneSup());

    if(AstBelt > 0)     //possibly display asteroid belt
        DisplayAsteroidBelt(ABelts[ABelts.size()-AstBelt]);

    printf("\n\n-------Outer  limit-------      %.3f AU", ThisStar.getOuterLimit());
}




int IsHabitable(float Dist, float InnerLimit,float  OuterLimit)
{
    if(Dist < InnerLimit)
        return 0;
    else if(Dist > OuterLimit)
        return 2;
    else
        return 1;
}


void setPlanets(Star *ThisStar)
{
    vector<Planet> System = ThisStar->getSystem();
    int NumberOfPlanets = (int)System.size();

    if(NumberOfPlanets <= 0)
        return;

    //float AverageEccentricity = 0.584*pow((float)NumberOfPlanets, -1.2);
    float StarMass = ThisStar->getMass();
    float InnerLimit = ThisStar->getRocheLimit();
    float OuterLimit = ThisStar->getOuterLimit();

    for(int i=0; i<NumberOfPlanets; i++)
    {
        System[i].setOrbitalValues(InnerLimit, OuterLimit, StarMass);
        System[i].setPhysicalValues(ThisStar->getLuminosity(), ThisStar->getMass());
    }
    ThisStar->setSystem(System);
}

int GasOrRock(float OrbitalRadius, float FrostZ)
{
    if(OrbitalRadius > FrostZ)
    {   //probably gas
        if(RandomInt(0,30)==1)
            return 0;
        else
            return 1;
    }
    else
    {
        if(RandomInt(0,50)==1)
            return 1;
        else
            return 0;
    }
}


void OrderPlanetsByDistance(vector<Planet> *StarSystem)
{
    if(StarSystem->size() == 0)
        return;

    Planet *NewArray = new Planet[StarSystem->size()];
    int systemSize = StarSystem->size();

    for(int i=0; i<systemSize; i++)
        NewArray[i] = (*StarSystem)[i];
    StarSystem->clear();

    sortPlanet(NewArray, systemSize);

    for(int i=0; i<systemSize; i++)
        StarSystem->push_back(NewArray[i]);

    delete NewArray;
}

void DisplayAsteroidBelt(AsteroidBelt ABelt)
{
  printf("\n\n--------------------------    -  %.3f AU", ABelt.getInnerEdge());
    printf("\n . °   o   ,    '     q  ,    |");
    printf("\n    `        .    °    .      |  %.3f AU width", ABelt.getWidth());
    printf("\n .    '   O     '             |");
    printf("\n--------------------------    -  %.3f AU\n", ABelt.getOuterEdge());
}

vector<AsteroidBelt> PlaceAsteroidBelts(Star StarSystem)
{
    if(DEBUG)
        printf("\nDebut Asteroid population");
        //deboguage a faire, lui arrive de planter
    vector<Planet> System = StarSystem.getSystem();
    vector<AsteroidBelt> NewBeltList;

    int PotentialAstNB=0;
    int systemSize = (int)System.size();

    for(int i=-1; i< systemSize; i++)
    {
        float Bi;
        if(i <= -1)
            Bi = StarSystem.getRocheLimit();
        else
            Bi = System[i].getOrbitalDistance();


        float Bo;
        if(i >= systemSize-1)
            Bo = StarSystem.getOuterLimit();
        else
            Bo = System[i+1].getOrbitalDistance();

        float Gap = Bo - Bi;
        //printf("\nBi %f, Bo %f, Gap : %f", Bi, Bo, Gap);
        if(Gap > 2.1)
            PotentialAstNB++;
        if(Gap > 2.1  && RandomInt(1,Gap) <  Gap-1)
        {   //Asteroid belt
            AsteroidBelt NewBelt;
            if(i == systemSize-1)
                NewBelt.setMidRange(Bo-Gap/3.0);
            else if(System[i+1].getMass() < System[i].getMass())
                NewBelt.setMidRange(Bo-Gap/3.0);
            else
                NewBelt.setMidRange(Bi+Gap/3.0);

            if(i == systemSize-1)   //last asteroid field before outer space
                NewBelt.setWidth(Gap*RandomFloat(0.20, 0.66));
            else
                NewBelt.setWidth(Gap*RandomFloat(0.25, 0.33));

            //if(NewBelt.getOuterEdge() < Bo)
                NewBeltList.push_back(NewBelt);
        }
    }
    if(DEBUG)
        printf("\nPotential asteroid belt number : %d\n", PotentialAstNB);
    return NewBeltList;
}

void sortPlanet(Planet Plan[], int number)
{   //sort an array of planets
    for(int i = 0; i < number - 1; i++)
    {
        Planet currentMin = Plan[i];
        int currentMinIndex = i;

        for(int j = i + 1; j < number; j++)
        {
            if(currentMin.getOrbitalDistance() > Plan[j].getOrbitalDistance())
            {
                currentMin = Plan[j];
                currentMinIndex = j;
            }
        }
            if(currentMinIndex != i){
                Plan[currentMinIndex] = Plan[i];
                Plan[i] = currentMin;
            }
        }
}

