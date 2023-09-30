#include "rtweekend.hpp"
#include <iostream>
#include <random>
#include "vec.hpp"
#include "color.hpp"
#include "sphere.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "camera.hpp"
#include "material.hpp"

int main()
{
	// camera
	camera cam;
	cam.aspect_ratio = 16. / 9.;
	cam.image_width = 400;
	cam.samples_per_pixel = 100;
	cam.max_depth = 50;

	auto material_ground = make_shared<lamabertian>(color(0.8, 0.8, 0.0));
	// auto material_center = make_shared<dielectric>(1.5);
	auto material_center = make_shared<lamabertian>(color(0.7, 0.3, 0.3));
	// auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8), 0.);
	auto material_left = make_shared<dielectric>(1.5);
	auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.);

	// World
	hittable_list world;
	world.add(make_shared<sphere>(point3(0., 0., -1.), 0.5, material_center));
	world.add(make_shared<sphere>(point3(0., -100.5, -1.), 100., material_ground));
	world.add(make_shared<sphere>(point3(-1., 0., -1.), 0.5, material_left));
	world.add(make_shared<sphere>(point3(-1., 0., -1.), -0.4, material_left));
	world.add(make_shared<sphere>(point3(1., 0., -1.), 0.5, material_right));

	cam.render(world);

	return 0;
}
