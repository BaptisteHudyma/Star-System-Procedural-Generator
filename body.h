#ifndef BODY_H
#define BODY_H

#include <math.h>
#include "orbit.h"
#include "bodyConsts.h"


class Body {
    public :
        double get_mass () const {return mass;};          //return stored mass
        double get_radius () const {return radius;};      //return stored radius

        double get_volume () const;		//calculate volume from radius
        double get_density () const;    //calculate density from volume and mass

        double get_Hill_limit (const Body&) const;	//
        double get_roche_limit (Body&) const;       //get roche limit
        
        Body& operator+= (const Body&);
        Body& operator= (const Body&);


        Orbit orbitParameters;	//orbit description

        virtual void show() const = 0;    //cout

    protected :

        double mass;		//Unit: earth mass or sun mass
        double radius;		//Unit: earth radius

    private :

};


#endif
