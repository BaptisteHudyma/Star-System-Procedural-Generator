#include "planet.h"
#include <iostream>

Planet::Planet (std::shared_ptr<Body> _orbiting, unsigned int seed, double _semiMajorAxis, double _mass) 
    : orbiting(_orbiting), rg(seed)
{
    mass = _mass;
    if (_orbiting == nullptr) {
        std::cout 
            << __FILE__ << " line " 
            << __LINE__ << ": fonction " 
            << TO_STR(Planet::Planet) << " "
            << ": a planet must orbit a body" 
            << std::endl;
        exit(0);
    }
    orbitParameters.semiMajorAxis = _semiMajorAxis;

    set_orbital_characteristics();
    set_physical_parameters ();
}

Planet::Planet (const Planet& other)
    : rg(other.rg.get_seed(), other.rg.get_count())
{
    
}


Planet::~Planet () {

}


double Planet::get_SOI () const {   //return the approximate sphere of influence of this body. Unit:AU
   return 0.9431 * orbitParameters.semiMajorAxis * pow (mass / orbiting->get_mass() , 2.0/5.0) ;
}


void Planet::set_orbital_characteristics () {
    //set orbit carac from star carac
    orbitParameters.eccentricity = rg.random_double (0.0, 0.078);

    orbitalPeriod = sqrt ( pow(orbitParameters.semiMajorAxis, 3.0) / orbiting->get_mass());
    orbitalVelocity = sqrt (orbiting->get_mass() / orbitParameters.semiMajorAxis);
    orbitParameters.inclination = rg.random_double (-2.0, 2.0);

    if (orbitParameters.inclination == 0.0)	{
        orbitParameters.longOfAscendingNode = 0; 
        orbitParameters.argumentOfPeriabsis = -1;
    }
    else	{
        orbitParameters.longOfAscendingNode = rg.random_double (0.0, 360.0);
        orbitParameters.argumentOfPeriabsis = rg.random_double (0.0, 180.0);
    }
}


void Planet::set_physical_parameters () {
    //set mass, radius and albedo
    if (mass <= 0) {    //mass not given by parent
        mass = rg.random_double (0.3, 4500.0);     //mass in Earth mass. 
    }

    if (mass < 4131) {      //4131 is the limit to brown dwarf transformation
        if (mass >= 317.2)	{ //electron degeneracy prevent the radius to grow more
            //317.2 earth mass is Jupiter mass
            albedo = 0.340;
            radius = 11.2 * rg.random_double (-0.2, 0.2);
            planetTypeStr = "Jupiterian gas giant";
        }
        else if (mass >= 19.9) {
            albedo = 0.340;
            if (rg.random_int(0, 10) < 2) {
                //low density Jupiter -> Type: puffy giant
                radius = rg.random_double (11.9, 21.28);    //radius from 1.1 to 1.9 the radius of Jupiter
                planetTypeStr = "puffy giant";
            }
            else {
                //saturnian gas giant
                radius = 1.2635 * log (mass) + 4.4921 + rg.random_double (-0.2, 0.2);
                planetTypeStr = "Saturnian gas giant";
            }
        }
        else if (mass >= 10.5) {    //Ice giant: small gas planet
            albedo = 0.29;
            radius = 1.6545 * pow (mass, 0.3564) + rg.random_double (-0.2, 0.2);
            planetTypeStr = "ice giant";
        }
        else if (mass >= 1.75) {
            //between ice giants and rocky
            //Super earth ?
            planetTypeStr = "super earth";

        }
        else if (mass >= 0.3) {
            //rocky planet
            planetTypeStr = "rocky planet";

        }
        else {
            //not really a planet, but a body that can't maintain it's shape with gravity
            planetTypeStr = "dwarf planet";

        }

    }
    else {
        //miniature brown star: failed star
        planetTypeStr = "small brown dwarf";

        mass = 	rg.random_double (4121.0 , 22824.0);
        radius = rg.random_double (11.5, 55.3);
        //temp = 1550.0 * pow (mass/0.05, 0.83 );

    }

    if (mass >= 10.5) {     //giants always have a ring system
        ringSystem = true;
    }

}



void Planet::show () const {
    std::cout << 
        "\tPlanet " << 
        planetTypeStr << 
        " with mass " << mass <<
        " eccentricity " << orbitParameters.eccentricity << 
        std::endl;
}




