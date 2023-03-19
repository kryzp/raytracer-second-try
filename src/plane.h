#ifndef PLANE_H
#define PLANE_H

#include "hittable.h"

class Plane : public Hittable
{
public:
	Plane();
	Plane(const Point3& c, const Vec3F& n, const Ref<Material>& m);

	bool hit(const Ray& r, double t_min, double t_max, Hit* hit) const override;

	Point3 centre;
	Vec3F normal;
	Ref<Material> material;
};

#endif // PLANE_H
