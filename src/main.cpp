#include <iostream>
#include <fstream>

#include "vec2.h"
#include "vec3.h"
#include "colour.h"
#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "hittable_group.h"
#include "camera.h"
#include "material.h"

Colour ray_colour(const Ray& r, const Hittable& world, int depth)
{
	if (depth <= 0) {
		return Colour::black();
	}

	Hit hit;
	if (world.hit(r, 0.001, INF, &hit))
	{
		Ray scattered;
		Colour attenuation;

		if (hit.material->scatter(r, hit, &attenuation, &scattered)) {
			Colour emission = hit.material->emit(hit.u, hit.v, hit.position);
			return emission + (attenuation * ray_colour(scattered, world, depth - 1));
		}

		return Colour::black();
	}

	// background
	Vec3F unit_dir = r.direction.normalized();
	double t = 0.5 * (unit_dir.y + 1.0);
	return (1.0 - t) * Colour(1, 1, 1) + t * Colour(0.15, 0.15, 0.35);
}

int main()
{
	// image
	const double ASPECT_RATIO = 16.0 / 9.0;
	const int WIDTH = 100;
	const int HEIGHT = static_cast<int>(WIDTH / ASPECT_RATIO);
	const int SAMPLES_PER_PIXEL = 1024;
	const int MAX_DEPTH = 32;

	std::ofstream image_output("../output.ppm");

	// world
	HittableGroup world;

	auto solidTex0 = create_ref<SolidTexture>(Colour(0.2, 0.8, 0.7));
	auto solidTex1 = create_ref<SolidTexture>(Colour(1.0, 0.9, 0.4));
	auto solidTex2 = create_ref<SolidTexture>(Colour(0.7, 0.2, 0.9));
	auto solidTex3 = create_ref<SolidTexture>(Colour(0.1, 0.2, 0.9));
	auto solidTex4 = create_ref<SolidTexture>(Colour(0.8, 0.8, 0.2));

	auto ground  = create_ref<Lambertian>(solidTex0);
	auto ground2 = create_ref<Lambertian>(solidTex4);
	auto centre  = create_ref<Dielectric>(solidTex2, 1.35);
	auto left    = create_ref<Lambertian>(solidTex1);
	auto right   = create_ref<Metal>     (solidTex3, create_ref<SolidTexture>(Colour::white() * 14), 0.0);

	world.add(create_ref<Plane>(Point3(0, 0, 1.5), Vec3F::backward(), ground2));
	world.add(create_ref<Plane>(Point3(0, -0.5, 0), Vec3F::up(), ground));
	world.add(create_ref<Sphere>(Point3(0, 0, 0), 0.5, centre));
	world.add(create_ref<Sphere>(Point3(-1, 1, 1), 0.5, left));
	world.add(create_ref<Sphere>(Point3(0, 0, -1.5), 0.25, right));

	// camera
	Point3 from(-4, 0.5, -1.5);
	Point3 to(0, 0, 1);
	Camera cam = Camera(from, to, Vec3F::up(), 30.0, ASPECT_RATIO, 0.1, (to - from).length());

	// render
	image_output << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";

	for (int i = HEIGHT - 1; i >= 0; i--)
	{
		std::cout << "\rScanlines Remaining: " << i << " " << std::flush;

		for (int j = 0; j < WIDTH; j++)
		{
			Colour px = Colour::empty();

			for (int s = 0; s < SAMPLES_PER_PIXEL; s++)
			{
				double u = ((double)j + randd()) / (WIDTH - 1);
				double v = ((double)i + randd()) / (HEIGHT - 1);

				Ray r = cam.get_ray(u, v);
				px += ray_colour(r, world, MAX_DEPTH);
			}

			image_output << px.write(std::cout, SAMPLES_PER_PIXEL);
		}
	}

	image_output.close();

    return 0;
}
