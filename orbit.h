#ifndef ORBIT_H
#define ORBIT_H


class Orbit {

    public:
        double get_periabsis () const;
        double get_apoabsis () const;
        double get_semiMinorAxis () const;

        //parameters
        double eccentricity;		//0 < e < 1
        double inclination;		//0-180 degrees : tilt of the orbit : 0-90 pro grade
        double semiMajorAxis;		//AU : distance to center of ellipse

        //position on orbit
        double longOfAscendingNode;	//0-360 degrees : inclination from ascending node (y axis)
        double argumentOfPeriabsis;	//0-360 degrees : position of the periabsis (z axis)
        double trueAnomaly;		//0-360 degrees : angle between periabsis and planet position

        //calculate when all system is generated
        double properSemiMajorAxis;
        double properEccentricity;
        double properInclination;

};


#endif
