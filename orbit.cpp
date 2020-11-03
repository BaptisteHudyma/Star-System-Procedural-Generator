#include "orbit.h"
#include <math.h>
#include <iostream>


double Orbit::get_periabsis () const {
    return semiMajorAxis * (1.0 - eccentricity); 
}

double Orbit::get_apoabsis () const { 
    return semiMajorAxis * (1.0 + eccentricity); 
}

double Orbit::get_semiMinorAxis () const {
    return semiMajorAxis * sqrt(1 - pow (eccentricity, 2.0)); 
}


