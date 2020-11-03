#include "star.h"
#include <math.h>
#include <iostream>


Star::Star (): rg(0) {
    //empty constructor
    mass = 0;
    luminosity = 0;
}

Star::Star (const Star& other): rg(other.rg.get_seed(), other.rg.get_count()) {
    //copy constructor
    this->operator=(other);
}

Star::Star (unsigned int seed): rg(seed) {
    //set star type from random generator
    set_star_type ();
    //set star class from random generator
    set_star_class ();
    //set star luminosity from random generator
    set_star_luminosity ();

    set_temperature_classification ();   //get random luminosity classification
    if (starType == O and starClass == V and tempClassification < 5)
        tempClassification = 5;     //max known classification for main sequence O star is 5
    else if (starType == M && tempClassification> 6)
        tempClassification = 6;

    set_temperature_from_Type_Class ();

    //if brown dwarf, select which one
    mass = get_mass_with_lum ();

}


Star::~Star() {

}

Star& Star::operator+= (const Star& other) {
    if (&other != this) {
        luminosity += other.luminosity;
        Body::operator+= (other);
    }
    return *this;
}

Star& Star::operator= (const Star& other) {
    if (&other != this) {
        starType = other.starType;
        starClass = other.starClass;
        luminosity = other.luminosity;
        metallicity = other.metallicity;
        externalLimit = other.externalLimit;
        tempClassification = other.tempClassification;
        surfaceTemperature = other.surfaceTemperature;

        Body::operator= (other);
    }
    return *this;
}


double Star::get_habitable_zone_lower () const {
    return sqrt (luminosity / 1.1);
}

double Star::get_habitable_zone_higher () const {
    return sqrt (luminosity / 0.53);
}

double Star::get_mass_with_temp () {    //deduce star mass from temperature (main sequences approx)
    return pow (surfaceTemperature / SUN_TEMP, 1.0 / 0.505);
}

double Star::get_mass_with_lum () {            //deduce star mass from luminosity (partial approx)
    if (luminosity < 0.03418801)
        return pow (luminosity, 1.0 / 2.3);
    else if (luminosity < 16.97056275)
        return pow (luminosity, 1.0 / 4.0);
    else if (luminosity < 64000)
        return pow (luminosity / 1.5, 1.0 / 3.5);
    else if (luminosity <= 160000)
        return pow (luminosity / 3200.0, 1.0);
    else 
        return pow (luminosity / 3200.0, 1.0 / 1.25);
}

void Star::set_temperature_from_Type_Class () {
    surfaceTemperature = TEMPS_SCALE_MINMAX [starType][1] + (TEMPS_SCALE_MINMAX [starType][2] * (9 - tempClassification));
    if (starType != UNDEFINED) {    //TEMPS_SCALE_MINMAX[starType] exists
        if (tempClassification == 0)
            surfaceTemperature += rg.random_int (- TEMPS_SCALE_MINMAX [starType][2] / 6, (int)TEMPS_SCALE_MINMAX [starType][2] / 6);
        else
            surfaceTemperature += rg.random_int (- TEMPS_SCALE_MINMAX [starType][2] / 2, (int)TEMPS_SCALE_MINMAX [starType][2] / 2);
    }
}

void Star::set_BV_index () {    //Ballero's formula
    colorBV = pow( (surfaceTemperature / 5601.0), -2/3) - 0.4;  
}

double Star::get_luminosity_from_radius_temperature () {
    //return the star luminosity in function of the luminosity of the sun
    return pow (get_radius(), 2.0) * pow (surfaceTemperature / SUN_TEMP, 4.0);
}

double Star::get_radius_from_luminosity_temperature () {
    //return star radius in function of the size of the sun
    return sqrt (luminosity / pow (surfaceTemperature / SUN_TEMP, 4.0));
}

void Star::set_temperature_classification() {
    //get random luminosity classification
    tempClassification = rg.random_int(0, 9); 
}

void Star::set_star_type () {
    //type of the star : O, B, A, ....
    int starClassProba = rg.random_int (1, 1000);
    if (starClassProba <= 2)	{
        //type O (proba 0.2)
        starType = O;
    }
    else if (starClassProba <= 4)	{
        //type B (proba 0.2)
        starType = B;
    }
    else if (starClassProba <= 11)	{
        //type A (proba 0.7)
        starType = A;
    }
    else if (starClassProba <= 13)	{
        //type F (proba 2)
        starType = F;
    }
    else if (starClassProba <= 68)	{
        //Type G (proba 3.5) (here 5.5)
        starType = G;
    }
    else if (starClassProba <= 148)	{
        //Type K (proba 8)
        starType = K;
    }
    else if (starClassProba <= 198)	{
        //Type D (proba 5)
        starType = D;
    }
    else if (starClassProba <= 900)	{
        //Type M (proba 80)
        starType = M;
    }
    else	{
        //L, T, Y, W, C, S
        //starType = UNDEFINED;
        starType = M;
    }
}

void Star::set_star_class () {
    //class of the star from star type : 0, I, II, ...
    int starClassProba = rg.random_int (0, 600); //should be 0-1000
    if (starClassProba <= 2 and starType != O)	{
        //hyper giant star 0,1
        starClass = O0;
    }
    else if	(starClassProba <= 10)	{
        //Super giant star 1
        starClass = I;
    }
    else if (starClassProba <= 60)	{
        //Bright giant star 5
        starClass = II;
    }
    else if (starClassProba <= 190)	{
        //Giant star 13
        starClass = III;
    }
    else if (starClassProba <= 200 and starType != M)	{
        //Sub giant star 10
        starClass = IV;
    }
    else	{
        //Main class star 65,9
        starClass = V;
    }
}


void Star::set_star_luminosity ()  {
    //get random luminosity from star class and type
    if (starType > D)	{
        std::cout 
            << __FILE__ << " line " 
            << __LINE__ << ": fonction " 
            << TO_STR(set_star_luminosity) << " "
            << ": No star class yet for " << starType 
            << std::endl;
        luminosity = 0;
        exit(0);
        return;
    }

    const double *lumClassTabRef = nullptr;
    switch (starClass)	{
        case O0:
            lumClassTabRef = LUM_CLASS_0[starType];
            break;
        case I:
            lumClassTabRef = LUM_CLASS_I[starType];
            break;
        case II:
            lumClassTabRef = LUM_CLASS_II[starType];
            break;
        case III:
            lumClassTabRef = LUM_CLASS_III[starType];
            break;
        case IV:
            lumClassTabRef = LUM_CLASS_IV[starType];
            break;
        case V:
            lumClassTabRef = LUM_CLASS_V[starType];
            break;
        default:
            std::cout 
                << __FILE__ << " line " 
                << __LINE__ << ": fonction " 
                << TO_STR(set_star_luminosity) << " "
                ": No star class for " << starClass 
                << std::endl;
            exit (0);
            break;
    }
    if (lumClassTabRef != nullptr) {
        luminosity = rg.random_double (lumClassTabRef[0], lumClassTabRef[1]);
    }
    else {
        std::cout 
            << __FILE__ << " line " 
            << __LINE__ << ": fonction " 
            << TO_STR(set_star_luminosity) << " "
            << ": Star luminosity tab is null for class " 
            << starClass 
            << std::endl;
        exit(0);
    }
}

void Star::set_spectral_color (double &r,double &g,double &b)
{ 
    // RGB <0,1> <- lambda l <400,700> [nm]
    double t;  r=0.0; g=0.0; b=0.0;
    double l = luminosity;

    //Red
    if ((l >= 400.0) && (l < 410.0)) {
        t = (l - 400.0) / (410.0 - 400.0);
        r = +(0.33 * t) - (0.20 * t * t);
    }
    else if ((l >= 410.0) && (l < 475.0)) {
        t = (l - 410.0) / (475.0 - 410.0);
        r = 0.14 - (0.13 * t * t);
    }
    else if ((l >= 545.0) && (l < 595.0)) {
        t = (l - 545.0) / (595.0 - 545.0);
        r = +(1.98 * t) - (t * t);
    }
    else if ((l >= 595.0) && (l < 650.0)) {
        t = (l - 595.0) / (650.0 - 595.0);
        r = 0.98 + (0.06*  t) - (0.40 * t * t);
    }
    else if ((l >= 650.0) && (l < 700.0)) {
        t = (l - 650.0) / (700.0 - 650.0);
        r = 0.65 - (0.84 * t) + (0.20 * t * t);
    }

    //Green
    if ((l >= 415.0) && (l < 475.0)) {
        t = (l - 415.0) / (475.0 - 415.0);
        g = +(0.80 * t * t);
    }
    else if ((l >= 475.0) && (l < 590.0)) {
        t = (l - 475.0) / (590.0 - 475.0);
        g = 0.8 + (0.76 * t) - (0.80 * t * t);
    }
    else if ((l >= 585.0) && (l < 639.0)) {
        t = (l - 585.0) / (639.0 - 585.0);
        g = 0.84 - (0.84 * t);
    }

    //Blue
    if ((l >= 400.0) && (l < 475.0)) {
        t = (l - 400.0) / (475.0 - 400.0);
        b = +(2.20 * t) - (1.50 * t * t);
    }
    else if ((l >= 475.0) && (l < 560.0)) {
        t = (l - 475.0) / (560.0 - 475.0);
        b = 0.7 - (t) + (0.30 * t * t);
    }
}





void Star::show() const {
    std::cout << 
        "Type " <<  
        STAR_TYPE_TO_STR [starType] << 
        tempClassification << 
        CLASS_TO_STR [starClass] << 
        ": " << STAR_TYPE_TO_COLOR_STR [starType] <<  
        " " << CLASS_TO_NAME_STR [starClass] << 
        " temp " << surfaceTemperature << 
        "K - Lum " << luminosity <<
        " Mass " << mass << 
        std::endl;
}





