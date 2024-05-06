#ifndef TEXTURE_H
#define TEXTURE_H

#include "rtweekend.hpp"
#include "color.hpp"

class texture
{
public:
    virtual ~texture() = default;

    virtual color value(double u, double v, const point3 &p) const = 0;
};

class solid_color : public texture
{
public:
    solid_color(color c) : color_value(c) {}

    solid_color(double red, double green, double blue) : color_value(color(red, green, blue)) {}

    color value(double u, double v, const point3 &p) const override
    {
        return color_value;
    }

private:
    color color_value;
};

#endif