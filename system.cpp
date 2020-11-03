#include "system.h"

#include <bits/stdc++.h>
#include <iostream>

System_Generator::System_Generator (unsigned int seed): rg(seed) 
{
    equivalentStar = std::make_shared<Star> ();

    generate_stars ();
    set_equivalent_star ();

    generate_planets ();
}

void System_Generator::show() {
    std::cout << "Stars" << std::endl;
    for (unsigned int i = 0; i < systemStars.size(); i++) {
        systemStars[i]->show();
    }
    std::cout << "Planets" << std::endl;
    for (unsigned int i = 0; i < systemPlanets.size(); i++) {
        systemPlanets[i]->show();
    }
}


void System_Generator::generate_stars () {
    for (int i = 0; i < rg.random_int(1, 3); i++) {
        std::shared_ptr<Star> newStar = std::make_shared<Star> (rg.random_int(0, INT_MAX));
        systemStars.push_back (newStar); 
    }
}


void System_Generator::set_equivalent_star () {
    *equivalentStar = *(systemStars[0]);    //equivalent star is set as the first
    for (unsigned int i = 1; i < systemStars.size(); i++) {
        std::shared_ptr<Star> tempStar = systemStars[i];

        //update equivalentStar
        *equivalentStar += *tempStar;
    }
}


void System_Generator::generate_planets () {

    for (int i = 0; i < rg.random_int(0, 10); i++) {
        systemPlanets.push_back (
                std::make_shared<Planet>(
                    equivalentStar, 
                    rg.random_int(0, INT_MAX), 
                    0.0
                    )
                ); 
    }
}


System_Generator::~System_Generator() {
    //empty planets
    systemPlanets.clear();

    //empty stars
    systemStars.clear();

}






