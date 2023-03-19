#ifndef COLOUR_H
#define COLOUR_H

#include <iostream>

#include "vec3.h"

struct Colour
{
	union
	{
		struct
		{
			double r;
			double g;
			double b;
		};

		double data[3];
	};

	Colour();
	Colour(double s);
	Colour(double r, double g, double b);
	Colour(const Vec3F& v);

	static const Colour& empty();
	static const Colour& black();
	static const Colour& white();
	static const Colour& red();
	static const Colour& green();
	static const Colour& blue();
	static const Colour& yellow();
	static const Colour& magenta();
	static const Colour& cyan();

	static Colour lerp(const Colour& from, const Colour& to, double amount);

	std::string write(std::ostream& out, int samples_per_pixel) const;

	bool operator == (const Colour& other) const;
	bool operator != (const Colour& other) const;

	Colour operator - () const;
	Colour operator - (const Colour& other) const;
	Colour operator + (const Colour& other) const;
	Colour operator * (const Colour& other) const;
	Colour operator / (const Colour& other) const;

	Colour& operator -= (const Colour& other);
	Colour& operator += (const Colour& other);
	Colour& operator *= (const Colour& other);
	Colour& operator /= (const Colour& other);
};

// global operators
inline Colour operator * (const Colour& lhs, double rhs) { return Colour(lhs.r * rhs, lhs.g * rhs, lhs.b * rhs); }
inline Colour operator * (double lhs, const Colour& rhs) { return Colour(rhs.r * lhs, rhs.g * lhs, rhs.b * lhs); }

#endif // COLOUR_H
