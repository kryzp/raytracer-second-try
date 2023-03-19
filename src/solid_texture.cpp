#include "texture.h"

SolidTexture::SolidTexture(const Colour& c)
	: colour(c)
{
}

Colour SolidTexture::sample(double u, double v, const Point3& p) const
{
	return colour;
}
