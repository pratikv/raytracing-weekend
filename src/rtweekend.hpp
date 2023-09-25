#ifndef RTWEEKEND_H
#define RTWEEKEND_H
#include <cmath>
#include <limits>
#include <memory>

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

#include "interval.hpp"
#include "ray.hpp"
#include "vec.hpp"

#endif