#include "plane.h"

Plane::Plane()
	: centre()
	, normal()
	, material()
{
}

Plane::Plane(const Point3& c, const Vec3F& n, const Ref<Material>& m)
	: centre(c)
	, normal(n)
	, material(m)
{
}

bool Plane::hit(const Ray& r, double t_min, double t_max, Hit* hit) const
{
	Point3 oc = r.position - centre;

	double time = -Vec3F::dot(oc, normal) / Vec3F::dot(r.direction, normal);

	if (Vec3F::dot(r.direction, normal) >= 0) {
		return false;
	}

	if (time < t_min || time > t_max) {
		return false;
	}

	hit->t = time;
	hit->position = r.at(hit->t);
	hit->set_face_normal(r, normal);
	hit->material = material;

	return true;
}
