#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.hpp"
#include "color.hpp"
#include "hittable.hpp"
#include "material.hpp"

class camera
{
public:
    double aspect_ratio = 1.;
    int image_width = 100;
    int samples_per_pixel = 10;
    int max_depth = 10;
    double vfov = 90;
    point3 look_from = point3(0., 0., -1.);
    point3 look_at = point3(0, 0, 0);
    vec3 vup = vec3(0, 1, 0);

    void render(const hittable &world)
    {
        initialize();
        // Render
        std::cout
            << "P3\n"
            << image_width << ' ' << image_height << "\n255\n";
        for (int j = 0; j < image_height; j++)
        {
            std::clog << "\nScanlines Remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++)
            {
                // auto pixel_color = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.);
                auto pixel_color = color(0., 0., 0.);
                for (int sample = 0; sample < samples_per_pixel; sample++)
                {
                    auto r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }

                write_color(std::cout, pixel_color, samples_per_pixel);
            }
        }
        std::clog << "\nDone.\n";
    }

private:
    int image_height;
    point3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    point3 center;
    vec3 u, v, w;
    void initialize()
    {
        image_height = static_cast<int>(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        // Camera
        auto focal_length = (look_at - look_from).length();
        auto theta = degrees_to_radians(vfov);
        double h = tan(theta / 2.);
        auto viewport_height = 2. * h * focal_length;
        auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
        center = look_from;

        w = unit_vector(look_from - look_at);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        vec3 viewport_u = viewport_width * u;
        vec3 viewport_v = viewport_height * -v;

        // auto viewport_u = vec3(viewport_width, 0., 0.);
        // auto viewport_v = vec3(0., -viewport_height, 0.);

        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        auto viewport_upper_left = center - (focal_length * w) - viewport_u / 2. - viewport_v / 2.;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    ray get_ray(int i, int j) const
    {
        auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
        auto pixel_sample = pixel_center + pixel_sample_square();
        auto ray_direction = pixel_sample - center;
        return ray(center, ray_direction);
    }

    vec3 pixel_sample_square() const
    {
        auto px = -0.5 + random_double();
        auto py = -0.5 + random_double();
        return (px * pixel_delta_u) + (py * pixel_delta_v);
    }

    color ray_color(const ray &r, int depth, const hittable &world) const
    {
        if (depth <= 0)
        {
            return color(0., 0., 0.);
        }
        hit_record rec;
        if (world.hit(r, interval(0.001, infinity), rec))
        {
            ray scattered;
            color attenuation;
            if (rec.mat->scatter(r, rec, attenuation, scattered))
            {
                return attenuation * ray_color(scattered, depth - 1, world);
            }
            return color(0., 0.0, 0.);
        }
        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return ((1.0 - a) * color(1.0, 1.0, 1.0)) + (a * color(0.5, 0.7, 1.0));
    }
};

#endif