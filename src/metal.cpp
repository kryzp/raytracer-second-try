#include "material.h"
#include "hittable.h"

Metal::Metal(const Ref<Texture>& a, const Ref<Texture>& e, double fz)
	: albedo(a)
	, emission(e)
	, fuzz(fz)
{
}

bool Metal::scatter(const Ray& in, const Hit& hit, Colour* attenuation, Ray* scattered) const
{
	Vec3F reflected = Vec3F::reflect(in.direction.normalized(), hit.normal);
	(*scattered) = Ray(hit.position, reflected + (Vec3F::in_unit_sphere() * fuzz));
	(*attenuation) = albedo->sample(hit.u, hit.v, hit.position);

	return Vec3F::dot(scattered->direction, hit.normal) > 0.0;
}

Colour Metal::emit(double u, double v, const Point3& p) const
{
	return emission->sample(u, v, p);
}
