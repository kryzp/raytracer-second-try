#include "camera.h"
#include "constants.h"

Camera::Camera(const Point3& look_from, const Point3& look_at, const Vec3F& up, double fov, double aspect, double aperture, double foc_d)
{
	double theta = DEG2RAD * fov;
	double h = std::tan(theta / 2.0);
	double viewport_height = 2.0 * h;
	double viewport_width = aspect * viewport_height;

	m_w = (look_at - look_from).normalized();
	m_u = Vec3F::cross(up, m_w).normalized();
	m_v = Vec3F::cross(m_w, m_u);

	m_origin = look_from;
	m_horizontal = foc_d * viewport_width * m_u;
	m_vertical = foc_d * viewport_height * m_v;

	m_lens_radius = aperture / 2.0;

	m_lower_left_corner =
		m_origin
		- (m_horizontal / 2.0)
		- (m_vertical / 2.0)
		+ (foc_d * m_w);
}

Ray Camera::get_ray(double u, double v) const
{
	Vec3F rd = m_lens_radius * Vec3F::in_unit_disk();
	Vec3F offset = (m_u * rd.x) + (m_v * rd.y);

	return Ray(
		m_origin + offset,
		m_lower_left_corner - m_origin - offset
			+ (u * m_horizontal)
			+ (v * m_vertical)
	);
}
