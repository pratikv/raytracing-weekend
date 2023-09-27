#include "rtweekend.hpp"
#include <iostream>
#include <random>
#include "vec.hpp"
#include "color.hpp"
#include "sphere.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "camera.hpp"

int main()
{
	// camera
	camera cam;
	cam.aspect_ratio = 16. / 9.;
	cam.image_width = 400;
	cam.samples_per_pixel = 100;

	// World
	hittable_list world;
	world.add(make_shared<sphere>(point3(0., 0., -1.), 0.5));
	world.add(make_shared<sphere>(point3(0., -100.5, -1.), 100.));

	cam.render(world);

	return 0;
}
