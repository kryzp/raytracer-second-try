#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray
{
public:
	Ray()
		: position()
		, direction()
	{
	}

	Ray(const Point3& orig, const Vec3F& dir)
		: position(orig)
		, direction(dir)
	{
	}

	Point3 at(double t) const { return position + (t * direction); }

	Point3 position;
	Vec3F direction;
};

#endif // RAY_H
