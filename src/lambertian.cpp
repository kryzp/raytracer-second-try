#include "material.h"
#include "hittable.h"

Lambertian::Lambertian(const Ref<Texture>& a)
	: albedo(a)
{
}

bool Lambertian::scatter(const Ray& in, const Hit& hit, Colour* attenuation, Ray* scattered) const
{
	Vec3F dir = hit.normal + Vec3F::random_unit();

	if (dir.near_zero()) {
		dir = hit.normal;
	}

	(*scattered) = Ray(hit.position, dir);
	(*attenuation) = albedo->sample(hit.u, hit.v, hit.position);

	return true;
}

Colour Lambertian::emit(double u, double v, const Point3& p) const
{
	return Colour::black();
}
