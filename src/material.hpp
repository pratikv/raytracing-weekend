#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.hpp"
#include "color.hpp"

class hit_record;

class material
{
public:
    virtual ~material() = default;

    virtual bool scatter(const ray &in, const hit_record &rec, color &attenuation, ray &scattered) const = 0;
};

class lamabertian : public material
{
public:
    lamabertian(const color &a) : albedo(a) {}

    bool scatter(const ray &in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        vec3 scattered_direction = rec.normal + random_unit_vector();
        if (scattered_direction.near_zero())
        {
            scattered_direction = rec.normal;
        }
        scattered = ray(rec.p, scattered_direction);
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
};

class metal : public material
{
public:
    metal(const color &a, double _fuzz) : albedo(a), fuzz(_fuzz < 1 ? _fuzz : 1) {}
    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        auto reflected_scattered = reflected + fuzz * random_unit_vector();
        scattered = ray(rec.p, reflected_scattered);
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
    double fuzz;
};

class dielectric : public material
{
public:
    dielectric(double _refraction_index) : ir(_refraction_index) {}
    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        attenuation = color(1., 1., 1.);
        double refraction_ratio = rec.front_face ? (1. / ir) : ir;
        vec3 unit_direction = unit_vector(r_in.direction());
        double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.);
        double sin_theta = sqrt(1 - (cos_theta * cos_theta));
        bool cannot_refract = (refraction_ratio * sin_theta) > 1.;
        vec3 direction;
        if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
        {
            direction = reflect(unit_direction, rec.normal);
        }
        else
        {
            direction = refract(unit_direction, rec.normal, refraction_ratio);
        }
        scattered = ray(rec.p, direction);
        return true;
    }

private:
    double ir;

    static double reflectance(double cosine, double ref_idx)
    {
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow(1 - cosine, 5);
    }
};

#endif