#ifndef MATERIAL_H
#define MATERIAL_H

#include "colour.h"
#include "ray.h"
#include "texture.h"

struct Hit;

class Material
{
public:
	virtual bool scatter(const Ray& in, const Hit& hit, Colour* attenuation, Ray* scattered) const = 0;
	virtual Colour emit(double u, double v, const Point3& p) const = 0;
};

class Lambertian : public Material
{
public:
	Lambertian(const Ref<Texture>& tex);

	bool scatter(const Ray& in, const Hit& hit, Colour* attenuation, Ray* scattered) const override;
	Colour emit(double u, double v, const Point3& p) const override;

	Ref<Texture> albedo;
};

class Metal : public Material
{
public:
	Metal(const Ref<Texture>& a, const Ref<Texture>& e, double fz);

	bool scatter(const Ray& in, const Hit& hit, Colour* attenuation, Ray* scattered) const override;
	Colour emit(double u, double v, const Point3& p) const override;

	Ref<Texture> albedo;
	Ref<Texture> emission;
	double fuzz;
};

class Dielectric : public Material
{
public:
	Dielectric(const Ref<Texture>& a, double ir);

	bool scatter(const Ray& in, const Hit& hit, Colour* attenuation, Ray* scattered) const override;
	Colour emit(double u, double v, const Point3& p) const override;

	Ref<Texture> albedo;
	double index_of_refraction;
};

#endif // MATERIAL_H
