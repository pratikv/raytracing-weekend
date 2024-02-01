#ifndef RTWEEKEND_H
#define RTWEEKEND_H
#include <cmath>
#include <limits>
#include <memory>
#include <random>

// usings
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.14159265358;

// utility functions
inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.;
}

inline double random_double()
{
    static std::uniform_real_distribution<double> distribution(0., 1.);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max)
{
    return min + (max - min) * random_double();
}

#include "interval.hpp"
#include "ray.hpp"
#include "vec.hpp"
#include "aabb.hpp"

#endif