#include "colour.h"

#include <cmath>

Colour::Colour()
	: r(0.0)
	, g(0.0)
	, b(0.0)
{
}

Colour::Colour(double s)
	: r(s)
	, g(s)
	, b(s)
{
}

Colour::Colour(double r, double g, double b)
	: r(r)
	, g(g)
	, b(b)
{
}

Colour::Colour(const Vec3F& v)
	: r(v.x)
	, g(v.y)
	, b(v.z)
{
}

Colour Colour::lerp(const Colour& from, const Colour& to, double amount)
{
	return Colour(
		std::lerp(from.r, to.r, amount),
		std::lerp(from.g, to.g, amount),
		std::lerp(from.b, to.b, amount)
	);
}

std::string Colour::write(std::ostream& out, int samples_per_pixel) const
{
	double rs = std::sqrt(r / static_cast<double>(samples_per_pixel));
	double gs = std::sqrt(g / static_cast<double>(samples_per_pixel));
	double bs = std::sqrt(b / static_cast<double>(samples_per_pixel));

	return
		  std::to_string(static_cast<int>(std::clamp(rs, 0.0, 0.999) * 256.0)) + " "
		+ std::to_string(static_cast<int>(std::clamp(gs, 0.0, 0.999) * 256.0)) + " "
		+ std::to_string(static_cast<int>(std::clamp(bs, 0.0, 0.999) * 256.0)) + "\n";
}

bool Colour::operator == (const Colour& other) const
{
	return (
		r == other.r &&
		g == other.g &&
		b == other.b
	);
}

bool Colour::operator != (const Colour& other) const
{
	return !(*this == other);
}

Colour Colour::operator - () const
{
	return Colour(
		1.0 - r,
		1.0 - g,
		1.0 - b
	);
}

Colour Colour::operator - (const Colour& other) const
{
	return Colour(
		this->r - other.r,
		this->g - other.g,
		this->b - other.b
	);
}

Colour Colour::operator + (const Colour& other) const
{
	return Colour(
		this->r + other.r,
		this->g + other.g,
		this->b + other.b
	);
}

Colour Colour::operator * (const Colour& other) const
{
	return Colour(
		this->r * other.r,
		this->g * other.g,
		this->b * other.b
	);
}

Colour Colour::operator / (const Colour& other) const
{
	return Colour(
		this->r / other.r,
		this->g / other.g,
		this->b / other.b
	);
}
Colour& Colour::operator -= (const Colour& other)
{
	(*this) = (*this) - other;
	return *this;
}

Colour& Colour::operator += (const Colour& other)
{
	(*this) = (*this) + other;
	return *this;
}

Colour& Colour::operator *= (const Colour& other)
{
	(*this) = (*this) * other;
	return *this;
}

Colour& Colour::operator /= (const Colour& other)
{
	(*this) = (*this) / other;
	return *this;
}

const Colour& Colour::empty()   { static const Colour EMPTY   = Colour(0.0, 0.0, 0.0); return EMPTY;   }
const Colour& Colour::black()   { static const Colour BLACK   = Colour(0.0, 0.0, 0.0); return BLACK;   }
const Colour& Colour::white()   { static const Colour WHITE   = Colour(1.0, 1.0, 1.0); return WHITE;   }
const Colour& Colour::red()     { static const Colour RED     = Colour(1.0, 0.0, 0.0); return RED;     }
const Colour& Colour::green()   { static const Colour GREEN   = Colour(0.0, 1.0, 0.0); return GREEN;   }
const Colour& Colour::blue()    { static const Colour BLUE    = Colour(0.0, 0.0, 1.0); return BLUE;    }
const Colour& Colour::yellow()  { static const Colour YELLOW  = Colour(1.0, 1.0, 0.0); return YELLOW;  }
const Colour& Colour::magenta() { static const Colour MAGENTA = Colour(1.0, 0.0, 1.0); return MAGENTA; }
const Colour& Colour::cyan()    { static const Colour CYAN    = Colour(0.0, 1.0, 1.0); return CYAN;    }
