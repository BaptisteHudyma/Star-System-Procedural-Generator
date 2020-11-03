#ifndef PLANET_CONSTS_H
#define PLANET_CONSTS_H

#define EARTH_DENSITY 5.51
#define EARTH_YEAR 365.25636


const double PLANET_COMPOSITION_COEFF [10][2] = {
    //constants to calculate mass radius approximation
    //Found experimentally by fitting a log curve to data
    //radius = [0] * pow(mass, [1])
    { 0.7965, 0.2549 }, //100% iron
    { 0.9412, 0.2646 }, //50% iron
    { 0.9860, 0.2677 }, //32.5% iron
    { 0.9969, 0.2682 }, //25% iron
    { 1.0073, 0.2690 }, //20 iron
    { 1.0496, 0.2719 }, //Mg/Si
    { 1.1657, 0.2695 }, //25% water / 52.5 MgSi / 22% iron
    { 1.2482, 0.2678 }, //45% water / 48,5% MgSi / 6.5% iron
    { 1.3892, 0.2661 }, //100% water
    { 1.8971, 0.4152 }, //100% Hydrogen
};

const double PLANET_ROCKY_COMPOSITION[3][10] = {   
    //probability of composition apparition of rocky planets
    //0: close to the star
    //1: in habitable zone (liquid water)
    //2: far from star

    //I                  R          W  H
    {2, 10, 17, 22, 22, 17,  8,  1, 0, 0},
    {1, 11, 15, 30, 15,  7,  9,  7, 5, 0},
    {0,  4, 11, 14, 15, 17, 17, 13, 9, 0}
};

const double PLANET_COMPOSITION_BY_TYPE[10][5] = {  
    //composition of planets for each type

    //Iron    R   W   He  Hy
    { 100,    0,  0,  0,  0 },
    {  50,   50,  0,  0,  0 },
    {32.5, 67.5,  0,  0,  0 },
    {  25,   75,  0,  0,  0 },
    {  20,   80,  0,  0,  0 },
    {   5,   95,  0,  0,  0 },
    {  22, 52.5, 25,  0,  0 },
    { 6.5, 48.5, 45,  0,  0 },
    {   1,    0, 99,  0,  0 },
    {   2,    0,  0, 95,  3 },
};


#endif
