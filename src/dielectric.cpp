#include "material.h"
#include "hittable.h"

static double _reflectance(double cost, double ref)
{
	double r0 = (1.0 - ref) / (1.0 + ref);
	r0 *= r0;
	return r0 + ((1.0 - r0) * std::pow(1.0 - cost, 5.0));
}

Dielectric::Dielectric(const Ref<Texture>& a, double ir)
	: index_of_refraction(ir)
	, albedo(a)
{
}

bool Dielectric::scatter(const Ray& in, const Hit& hit, Colour* attenuation, Ray* scattered) const
{
	(*attenuation) = albedo->sample(hit.u, hit.v, hit.position);
	double ratio = hit.front_face ? (1.0 / index_of_refraction) : index_of_refraction;

	Vec3F dir = in.direction.normalized();

	double cost = std::min(Vec3F::dot(-dir, hit.normal), 1.0);
	double sint = std::sqrt(1.0 - (cost * cost));

	bool cannot_refract = (ratio * sint) > 1.0;

	Vec3F new_direction;

	if (cannot_refract || (_reflectance(cost, ratio) > randd())) {
		new_direction = Vec3F::reflect(dir, hit.normal);
	} else {
		new_direction = Vec3F::refract(dir, hit.normal, ratio);
	}

	(*scattered) = Ray(hit.position, new_direction);

	return true;
}

Colour Dielectric::emit(double u, double v, const Point3& p) const
{
	return Colour::black();
}
