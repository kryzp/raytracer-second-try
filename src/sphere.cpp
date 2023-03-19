#include "sphere.h"

Sphere::Sphere()
	: centre()
	, radius()
{
}

Sphere::Sphere(const Point3& c, double r, const Ref<Material>& m)
	: centre(c)
	, radius(r)
	, material(m)
{
}

bool Sphere::hit(const Ray& r, double t_min, double t_max, Hit* hit) const
{
	Point3 oc = r.position - centre;
	double a = r.direction.length_squared();
	double h = Vec3F::dot(oc, r.direction);
	double c = oc.length_squared() - (radius * radius);
	double D = (h * h) - (a * c);

	if (D < 0) {
		return false;
	}

	double sqrtd = std::sqrt(D);

	double root = (-h - sqrtd) / a;
	if (root < t_min || t_max < root) {
		root = (-h + sqrtd) / a;
		if (root < t_min || t_max < root) {
			return false;
		}
	}

	hit->t = root;
	hit->position = r.at(hit->t);
	Vec3F n = (hit->position - centre) / radius;
	hit->set_face_normal(r, n);
	hit->material = material;

	return true;
}
