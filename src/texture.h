#ifndef TEXTURE_H
#define TEXTURE_H

#include "colour.h"

class Texture
{
public:
	virtual Colour sample(double u, double v, const Point3& p) const = 0;
};

class SolidTexture : public Texture
{
public:
	SolidTexture(const Colour& c);

	Colour sample(double u, double v, const Point3& p) const override;

	Colour colour;
};

#endif // TEXTURE_H
