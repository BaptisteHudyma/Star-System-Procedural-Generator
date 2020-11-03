#ifndef STAR_H
#define STAR_H

#include "body.h"
#include "starConsts.h"
#include "random.h"

//transform anything to text
#define TO_STR(s) #s


#include <memory>

class Star : public Body {
    public:
        explicit Star ();
        explicit Star (const Star&);
        explicit Star (unsigned int seed);
        ~Star();

        /*
         *     GETs 
         */
        int get_type () const { return starType; };
        int get_class () const { return starClass; };
        double get_luminosity () const { return luminosity; };
        int get_temperature_class () const { return tempClassification; };               //get temperate classification (0 to 9)
        unsigned int get_surface_temperature () const { return surfaceTemperature; };

        double get_habitable_zone_lower () const;           //get star's habitable zone lower limite (AU)
        double get_habitable_zone_higher () const;          //get star's habitable zone higher limit (AU)

        Star& operator+= (const Star&);
        Star& operator= (const Star&);
        void show () const;

        /*
         *    SETs
         */


    protected:
        //classification
        int starType;           //star type (O - A- ... - M)
        int starClass;          //star class (O - I - II - .. - V) 
        int tempClassification; //0-9 luminosity classification

        //physical
        unsigned int surfaceTemperature;      //star Photosphere Temperature (K)
        double luminosity;	    //Unit: sun luminosity
        double metallicity;
        double colorBV;         //BV color index
        unsigned int age;       //in million years

        //effects
        double externalLimit;	//Unit: AU

    private:
        Random_Generator rg;    //this star random generator

        //Init
        void set_star_type ();          //set random star type
        void set_star_class ();         //set random star class
        void set_star_luminosity ();    //set random luminosity from class and type
        void set_temperature_classification();   //get random luminosity classification
        void set_temperature_from_Type_Class ();
        void set_BV_index ();           //set BV color index from temperature

        //Utils
        double get_mass_with_temp ();    //deduce star mass from temperature (main sequences approx)
        double get_mass_with_lum ();            //deduce star mass from luminosity (main sequence approx)
        double get_radius_from_luminosity_temperature (); 
        double get_luminosity_from_radius_temperature ();
        void set_spectral_color (double &,double &,double &);    //get RGB spectral color from luminosity


};






#endif
