#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec3.h"
#include "ray.h"

class Material;

struct Hit
{
	Point3 position;
	Vec3F normal;
	double t;
	double u, v;
	bool front_face;
	Ref<Material> material;

	void set_face_normal(const Ray& r, const Vec3F& outward_normal) {
		front_face = Vec3F::dot(r.direction, outward_normal) < 0.0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class Hittable
{
public:
	virtual bool hit(const Ray& r, double t_min, double t_max, Hit* hit) const = 0;
};

#endif // HITTABLE_H
