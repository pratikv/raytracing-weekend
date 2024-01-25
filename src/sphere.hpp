#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.hpp"

class sphere : public hittable
{
private:
    point3 center1;
    double radius;
    shared_ptr<material> mat;
    bool is_moving;
    vec3 center_vec;

    point3 center(double time) const
    {
        return center1 + center_vec * time;
    }

public:
    sphere(point3 _center, double _radius, shared_ptr<material> _material) : center1(_center), radius(_radius), mat(_material), is_moving(false) {}
    sphere(point3 _center1, point3 _center2, double _radius, shared_ptr<material> _material) : center1(_center1), radius(_radius), mat(_material), is_moving(true)
    {
        center_vec = _center2 - _center1;
    }

    bool hit(const ray &r, interval ray_t, hit_record &rec) const
    {
        point3 center = is_moving ? sphere::center(r.time()) : center1;
        vec3 oc = r.origin() - center;
        auto a = r.direction().length_squared(); //(r.direction(), r.direction());
        auto half_b = dot(oc, r.direction());
        auto c = oc.length_squared() - (radius * radius);
        auto discriminant = (half_b * half_b) - (a * c);
        if (discriminant < 0.)
        {
            return false;
        }
        auto root = (-half_b - sqrt(discriminant)) / a;
        if (!ray_t.surrounds(root))
        {
            root = (-half_b + sqrt(discriminant)) / a;
            if (!ray_t.surrounds(root))
            {
                return false;
            }
        }
        rec.t = root;
        rec.p = r.at(root);
        auto outward_normal = (rec.p - center1) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat;
        return true;
    }
};

#endif