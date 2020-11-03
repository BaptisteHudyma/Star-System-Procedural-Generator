#include "body.h"

double Body::get_Hill_limit (const Body& secondary) const {
    //distance under which this body as the dominant gravitational pull
    if (secondary.mass == 0)
        return 0;
    return orbitParameters.get_periabsis () * pow (mass / (3.0 * secondary.mass), 1.0 / 3.0 );
}

double Body::get_roche_limit(Body& secondary) const {
    //minimum distance after which a satellite can be maintained by it's own gravitational pull
    return radius * pow ( 2.0 * get_density() / secondary.get_density(), 1.0 / 3.0);
}

double Body::get_volume () const {
    return pow (radius, 3.0);
}

double Body::get_density () const {
    if (mass == 0)
        return 0;
    return mass / get_volume ();
}


Body& Body::operator= (const Body& other) {
    //add mass
    if (&other != this) {
        mass = other.mass;
        radius = other.radius;
    }
    return *this;
}

Body& Body::operator+= (const Body& other) {
    //add mass
    if (&other != this) {
        mass += other.mass;
    }
    return *this;
}
