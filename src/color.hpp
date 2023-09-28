#ifndef COLOR_H
#define COLOR_H

#include "vec.hpp"

#include <iostream>

using color = vec3;

inline double linear_to_double(double linear_component)
{
    return sqrt(linear_component);
}

void write_color(std::ostream &out, color pixel_color, int sample_per_pixel)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    auto scale = 1. / sample_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    r = linear_to_double(r);
    g = linear_to_double(g);
    b = linear_to_double(b);

    static const interval intensity(0.000, 0.999);

    out << static_cast<int>(256 * intensity.clamp(r)) << ' '
        << static_cast<int>(256 * intensity.clamp(g)) << ' '
        << static_cast<int>(256 * intensity.clamp(b)) << '\n';
}

#endif