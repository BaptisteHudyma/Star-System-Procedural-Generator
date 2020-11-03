#ifndef SYSTEM_H
#define SYSTEM_H

#include "star.h"
#include "planet.h"
#include "random.h"

#include <memory>


class System_Generator {  //system represented by an equivalent star 
    public:
        explicit System_Generator (unsigned int seed);
        ~System_Generator();    //destruct

        void show();

    protected:
        void generate_stars ();         //generate the center stars
        void set_equivalent_star();     //set the parameters for this system equivalent star
        void generate_planets ();


    private:
        std::vector<std::shared_ptr<Star>> systemStars;
        std::vector<std::shared_ptr<Planet>> systemPlanets;
        std::shared_ptr<Star> equivalentStar;

        Random_Generator rg;
};




#endif
