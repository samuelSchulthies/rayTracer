#pragma once

#include <random>

using namespace std;

inline double randomDouble() {
    static uniform_real_distribution<double> distribution(0.0, 1.0);
    static mt19937 generator;
    return distribution(generator);
}

inline double randomDouble(double min, double max) {
    return min + (max - min) * randomDouble();
}
