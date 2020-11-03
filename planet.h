#ifndef PLANET_H
#define PLANET_H

#include "body.h"
#include "random.h"
#include <memory>

//transform anything to text
#define TO_STR(s) #s

class Planet : public Body {
    public:
        explicit Planet (std::shared_ptr<Body> orbiting, unsigned int seed, double sma, double mass=0);
        explicit Planet (const Planet&);
        ~Planet();

        double get_SOI () const;        //Sphere of influence. Unit: AU
        bool is_habitable ();           //Planet is in habitable zone
        void show () const;

    protected:
        void set_orbital_characteristics ();    //set orbit carac from star carac
        void set_physical_parameters ();        //set mass, albedo, temperature  and composition

    private:
        double surfaceGravity;  //Unit: g/m3
        double albedo;          //0 to 1
        double axialTilt;       //degrees

        bool ringSystem;            //true if has ring system
        std::string planetTypeStr;  //Planet type as String

        //Orbit 
        double distFromStar;    //distance from star in AU
        double orbitalPeriod;   //Unit: earth years
        double orbitalVelocity;   //Unit: earth velocity

        std::shared_ptr<Body> orbiting;		    //Star that this planet is orbiting
        Random_Generator rg;



    public:
        //getters
        double get_albedo () const { return albedo; };
        double get_orbital_period () const { return orbitalPeriod; }; 	//Unit: earth years
        double get_surface_gravity () const { return surfaceGravity; };
        std::string get_type_as_str () const { return planetTypeStr; };
        double get_orbital_velocity () const { return orbitalVelocity; };
        double get_distance_from_star () const { return distFromStar; };

};


#endif
