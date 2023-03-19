#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class Sphere : public Hittable
{
public:
	Sphere();
	Sphere(const Point3& c, double r, const Ref<Material>& m);

	bool hit(const Ray& r, double t_min, double t_max, Hit* hit) const override;

	Point3 centre;
	double radius;
	Ref<Material> material;
};

#endif // SPHERE_H
