
#include "random.h"
#include <bits/stdc++.h>
#include <math.h>

Random_Generator::Random_Generator(unsigned int seed, unsigned int count) 
    : seed(seed), count(count), randGene(seed), randomGenerator(0.0, 1.0), randomGaussianGenerator(0.0, 1.0)
{
    //set generator count
    for (unsigned int i = 0; i < count; i++) {
        randomGenerator(randGene);
        randomGaussianGenerator(randGene);
    }
}



template<typename T> 
T Random_Generator::random(const T lowerBorn, const T higherBorn) {
    count += 1;
    return (lowerBorn + randomGenerator(randGene) * (higherBorn - lowerBorn));
}

int Random_Generator::random_int(const int lowerBorn, const int higherBorn) {
    //count += 1;
    //return (int)(lowerBorn + randomGenerator(randGene) * (higherBorn - lowerBorn));
    return random<int>(lowerBorn, higherBorn);
}

double Random_Generator::random_double (const double lowerBorn, const double higherBorn) {
    //count += 1;
    //return lowerBorn + randomGenerator(randGene) * (higherBorn - lowerBorn);
    return random<double>(lowerBorn, higherBorn);
}


double Random_Generator::gaussian(double center, double var) {
    //(1.0 / (var * pow(2.0 * M_PI, 0.2))) * 
    return 0;
}


double Random_Generator::get_composed_gaussian (double center, double var) {
    double gauss = randomGaussianGenerator(randGene);
    return (gauss * var + center);
}





