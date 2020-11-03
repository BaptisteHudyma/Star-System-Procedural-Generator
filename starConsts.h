#ifndef STARCONSTS_H
#define STARCONSTS_H


#define SUN_TEMP 5766
#define PI 3.141592653
#define SUN_RADIUS_KM 696392
#define SUN_RADIUS_AU 0.00465047
#define SUN_DENSITY 1.408

#include<string>

enum StarType {
	O,	//ultraviolet/blue (30K/52K K)
	B,	//blue (10K/30K K)
	A,	//white blue
	F,	//white yellow (6K/7600 K)
	G,	//yellow orange (5300/6000 K)
	K,	//orange red
	M,	//red (~5000 K)
	D, 	//Degenerate
	S, 	//carbon/oxygen stars
	C,	//carbon star (3450/5100 K)
	L,	//brown dwarf (1300/2800 K), dark red/infrared 
	T,	//methane dwarf (550/1300 K), infrared
	Y,	//brown ammonia dwarf (250/400 K)
	WR,	//Wolf-Rayet

    UNDEFINED, //No type
};

const std::string STAR_TYPE_TO_STR [15] {
	"O",	//ultraviolet/blue (30K/52K K)
	"B",	//blue (10K/30K K)
	"A",	//white blue
	"F",	//white yellow (6K/7600 K)
	"G",	//yellow orange (5300/6000 K)
	"K",	//orange red
	"M",	//red (~5000 K)
	"D", 	//Degenerate
	"S", 	//carbon/oxygen stars
	"C",	//carbon star (3450/5100 K)
	"L",	//brown dwarf (1300/2800 K), dark red/infrared 
	"T",	//methane dwarf (550/1300 K), infrared
	"Y",	//brown ammonia dwarf (250/400 K)
	"WR",	//Wolf-Rayet
    "UNDEFINED", //No type
};

const std::string STAR_TYPE_TO_COLOR_STR [15] = {
	"ultraviolet/blue",
	"blue",
    "white blue",
	"white yellow",
	"yellow orange",
	"orange red",
	"red",
	"Degenerate",
	"carbon/oxygen",
	"carbon",
	"dark red/infrared",
	"infrared",
	"brown",
	"WR",	//Wolf-Rayet

    "UNDEFINED", //No type
};

//star class
enum {
    O0, 
    I, 
    II, 
    III, 
    IV, 
    V
};
const std::string CLASS_TO_NAME_STR [6] {
    /*O*/  "hypergiant",
	/*I*/  "supergiant",
    /*II*/ "bright giant",
	/*III*/"giant",
	/*IV*/ "subdwarf",
	/*V*/  "dwarf",
};
const std::string CLASS_TO_STR [6] {
    /*O*/  "O",
	/*I*/  "I",
    /*II*/ "II",
	/*III*/"III",
	/*IV*/ "IV",
	/*V*/  "V",
};

const double LUM_CLASS_V [7][2] =
{   //Main class : dwarf star
	// Lmin, Lmax
	/*O*/  {20000,    800000},
	/*B*/  {80,       20000},
	/*A*/  {6.5,      80},
	/*F*/  {1.26,     6.5 },
	/*G*/  {0.42,     1.26 },
	/*K*/  {0.072,    0.42 },
	/*M*/  {0.000015, 0.072 }
};
const double LUM_CLASS_IV [7][2] =
{   //Sub giant star
	// Lmin, Lmax
	/*O*/  {80000, 100000},
	/*B*/  {102,   34000},
	/*A*/  {13,    102},
	/*F*/  {9,     13 },
	/*G*/  {8,     9 },
	/*K*/  {8,     9 },
	/*M*/  {9,     10}
};
const double LUM_CLASS_III [7][2] =
{   //Giant star
	// Lmin, Lmax
	/*O*/  {500000, 300000},
	/*B*/  {170,    500000},
	/*A*/  {97,     170},
	/*F*/  {95,     97 },
	/*G*/  {95,     96 },
	/*K*/  {96,     98 },
	/*M*/  {98,     105 }
};
const double LUM_CLASS_II [7][2] =
{   //Bright giant star
	// Lmin, Lmax
	/*O*/  {40000, 52000},
	/*B*/  {4000,  40000},
	/*A*/  {2000,  4000},
	/*F*/  {960,   2000 },
	/*G*/  {950,   960 },
	/*K*/  {950,   1000 },
	/*M*/  {1000,  8000 }
};
const double LUM_CLASS_I [7][2] =
{   //Super giant star
	// Lmin, Lmax
	/*O*/  {10000, 1500000},
	/*B*/  {10000, 1500000},
	/*A*/  {1000,  100000},
	/*F*/  {1000,  100000 },
	/*G*/  {20000, 500000 },
	/*K*/  {20000, 500000 },
	/*M*/  {20000, 500000 }
};
const double LUM_CLASS_0 [7][2] =
{   //hyper giant star
	// Lmin, Lmax
	/*O*/  {1000000, 5000000},
	/*B*/  {380000,  2000000},
	/*A*/  {300000,  600000 },
	/*F*/  {300000,  600000 },
	/*G*/  {100000,  500000 },
	/*K*/  {100000,  500000 },
	/*M*/  {86000,   500000 }
};
const double LUM_CLASS_D [7][2] =
{   //white dwarf
	/*O*/  {0.2,     1},
	/*B*/  {0.06,    0.2},
	/*A*/  {0.0006 , 0.06},
	/*F*/  {0.0002 , 0.0006 },
	/*G*/  {0.00009, 0.0002 },
	/*K*/  {0.00008, 0.00009 },
	/*M*/  {0.00005, 0.00008 }
};

//Temperature Scale minimum and maximum
const int TEMPS_SCALE_MINMAX [9][3] =
{       //Tmax,  Tmin, coeff
	/*O*/  {54000,  33200, 2400},
	/*B*/  {29700,  10700, 2111},
	/*A*/  {9790,   7323,  274},
	/*F*/  {7300,   6033,  141},
	/*G*/  {5940,   5335,  67},
	/*K*/  {5150,   3880,  141},
	/*M*/  {3840,   2376,  165},
	/*D*/  {40000,  4000,  8000},
	/*Un*/ {0,      0,     0}
};


#endif
