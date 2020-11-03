#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random_Generator {
    public:
        Random_Generator (unsigned int seed, unsigned int count=0);

        template<typename T> T random(const T, const T);

        int random_int (const int, const int);
        double random_double (const double, const double);

        unsigned int get_seed() const { return seed; };
        unsigned int get_count() const { return count; };

        double get_composed_gaussian (double, double);
        double gaussian(double center, double var);

    protected:
        const unsigned int seed;
        unsigned int count; //count how many times we called this generator

    private:
        std::mt19937 randGene;
        std::uniform_real_distribution<double> randomGenerator;
        //std::lognormal_distribution<double> randomGaussianGenerator;
        std::normal_distribution<double> randomGaussianGenerator;
};


#endif
