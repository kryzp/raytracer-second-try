#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

class Camera
{
public:
	Camera(const Point3& look_from, const Point3& look_at, const Vec3F& up, double fov, double aspect, double aperture, double foc_d);

	Ray get_ray(double u, double v) const;

private:
	Point3 m_origin;
	Point3 m_lower_left_corner;
	Vec3F m_horizontal;
	Vec3F m_vertical;
	Vec3F m_u, m_v, m_w;
	double m_lens_radius;
};

#endif // CAMERA_H
