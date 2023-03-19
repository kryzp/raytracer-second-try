#ifndef VEC3_H
#define VEC3_H

#include "vec2.h"
#include "constants.h"

#include <cmath>

template <typename T>
struct Vec3
{
	union
	{
		struct
		{
			T x;
			T y;
			T z;
		};

		T data[3];
	};

	Vec3();
	Vec3(T s);
	Vec3(T x, T y, T z);
	explicit Vec3(const Vec2<T>& xy);

	// enable implicit casting to other vectors
	template <typename Y>
	Vec3(const Vec3<Y>& other) noexcept
		: x(other.x)
		, y(other.y)
		, z(other.z)
	{
	}

	static const Vec3& unit();
	static const Vec3& zero();
	static const Vec3& one();
	static const Vec3& left();
	static const Vec3& right();
	static const Vec3& up();
	static const Vec3& down();
	static const Vec3& forward();
	static const Vec3& backward();

	static Vec3 from_angle(double theta, double phi, double length);
	static Vec3 lerp(const Vec3& from, const Vec3& to, double amount);
	static double dot(const Vec3& a, const Vec3& b);
	static Vec3 cross(const Vec3& a, const Vec3& b);
	static Vec3 reflect(const Vec3& v, const Vec3& n);
	static Vec3 refract(const Vec3& uv, const Vec3& n, double n21);

	static Vec3 random();
	static Vec3 random(double mn, double mx);
	static Vec3 in_unit_sphere();
	static Vec3 in_unit_disk();
	static Vec3 random_unit();

	bool near_zero() const;

	double length() const;
	double length_squared() const;

	Vec3 abs() const;
	Vec3 normalized() const;
	Vec2<T> xy() const;

	bool operator == (const Vec3& other) const;
	bool operator != (const Vec3& other) const;

	Vec3<T> operator + (const Vec3& other) const;
	Vec3<T> operator - (const Vec3& other) const;
	Vec3<T> operator * (const Vec3& other) const;
	Vec3<T> operator / (const Vec3& other) const;

	Vec3<T> operator - () const;

	Vec3<T>& operator += (const Vec3& other);
	Vec3<T>& operator -= (const Vec3& other);
	Vec3<T>& operator *= (const Vec3& other);
	Vec3<T>& operator /= (const Vec3& other);
};

// global operators
template <typename T> Vec3<T> operator * (const Vec3<T>& lhs, double rhs) { return Vec3<T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs); }
template <typename T> Vec3<T> operator * (double lhs, const Vec3<T>& rhs) { return Vec3<T>(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs); }

using Vec3F		= Vec3<double>;
using Vec3I		= Vec3<int>;
using Vec3U		= Vec3<unsigned>;

using Size3		= Vec3<double>;
using Int3		= Vec3<int>;
using Point3	= Vec3<double>;
using UInt3		= Vec3<unsigned>;
using Unsigned3 = Vec3<unsigned>;

template <typename T>
Vec3<T>::Vec3()
	: x(0.0), y(0.0), z(0.0)
{
}

template <typename T>
Vec3<T>::Vec3(T s)
	: x(s), y(s), z(s)
{
}

template <typename T>
Vec3<T>::Vec3(T x, T y, T z)
	: x(x), y(y), z(z)
{
}

template <typename T>
Vec3<T>::Vec3(const Vec2<T>& xy)
	: x(xy.x), y(xy.y), z(0.0f)
{
}

template <typename T>
Vec3<T> Vec3<T>::from_angle(double theta, double phi, double length)
{
	return Vec3(
		std::cosf(phi) * length,
		std::sinf(phi) * length,
		std::sinf(theta) * length
	);
}

template <typename T>
double Vec3<T>::dot(const Vec3<T>& a, const Vec3<T>& b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

template <typename T>
Vec3<T> Vec3<T>::cross(const Vec3<T>& a, const Vec3<T>& b)
{
	return Vec3(
		(a.y * b.z) - (a.z * b.y),
		(a.z * b.x) - (a.x * b.z),
		(a.x * b.y) - (a.y * b.x)
	);
}

template <typename T>
Vec3<T> Vec3<T>::reflect(const Vec3<T>& v, const Vec3<T>& n)
{
	return v - (2 * dot(v, n) * n);
}

template <typename T>
Vec3<T> Vec3<T>::refract(const Vec3<T>& uv, const Vec3<T>& n, double n21)
{
	double cost = std::min(dot(-uv, n), 1.0);
	Vec3 out_perp = n21 * (uv + (cost * n));
	Vec3 out_para = -std::sqrt(std::abs(1.0 - out_perp.length_squared())) * n;
	return out_perp + out_para;
}

template <typename T>
Vec3<T> Vec3<T>::lerp(const Vec3& from, const Vec3& to, double amount)
{
	return Vec3(
		std::lerp(from.x, to.x, amount),
		std::lerp(from.y, to.y, amount),
		std::lerp(from.z, to.z, amount)
	);
}

template <typename T>
Vec3<T> Vec3<T>::random()
{
	return Vec3<T>(randd(), randd(), randd());
}

template <typename T>
Vec3<T> Vec3<T>::random(double mn, double mx)
{
	return Vec3<T>(randd(mn, mx), randd(mn, mx), randd(mn, mx));
}

template <typename T>
Vec3<T> Vec3<T>::in_unit_sphere()
{
	while (true) {
		Vec3<T> p = Vec3<T>::random(-1.0, +1.0);
		if (p.length_squared() >= 1.0) {
			continue;
		}
		return p;
	}
}

template <typename T>
Vec3<T> Vec3<T>::in_unit_disk()
{
	while (true) {
		Vec3<T> p = Vec3<T>(randd(-1.0, +1.0), randd(-1.0, +1.0), 0.0);
		if (p.length_squared() >= 1.0) {
			continue;
		}
		return p;
	}
}

template <typename T>
Vec3<T> Vec3<T>::random_unit()
{
	return in_unit_sphere().normalized();
}

template <typename T>
bool Vec3<T>::near_zero() const
{
	const double s = 1e-8;
	return (std::abs(x) < s) && (std::abs(y) < s) && (std::abs(z) < s);
}

template <typename T>
double Vec3<T>::length() const
{
	return std::sqrtf(length_squared());
}

template <typename T>
double Vec3<T>::length_squared() const
{
	return (x * x) + (y * y) + (z * z);
}

template <typename T>
Vec3<T> Vec3<T>::abs() const
{
	return Vec3(
		std::abs(this->x),
		std::abs(this->y),
		std::abs(this->z)
	);
}

template <typename T>
Vec3<T> Vec3<T>::normalized() const
{
	double len = length();

	if (len == 0.0f) {
		return zero();
	}

	return Vec3(
		x / len,
		y / len,
		z / len
	);
}

template <typename T>
Vec2<T> Vec3<T>::xy() const
{
	return Vec2<T>(
		this->x,
		this->y
	);
}

template <typename T> bool Vec3<T>::operator == (const Vec3& other) const { return this->x == other.x && this->y == other.y && this->z == other.z; }
template <typename T> bool Vec3<T>::operator != (const Vec3& other) const { return !(*this == other); }

template <typename T> Vec3<T> Vec3<T>::operator + (const Vec3& other) const { return Vec3(this->x + other.x, this->y + other.y, this->z + other.z); }
template <typename T> Vec3<T> Vec3<T>::operator - (const Vec3& other) const { return Vec3(this->x - other.x, this->y - other.y, this->z - other.z); }
template <typename T> Vec3<T> Vec3<T>::operator * (const Vec3& other) const { return Vec3(this->x * other.x, this->y * other.y, this->z * other.z); }
template <typename T> Vec3<T> Vec3<T>::operator / (const Vec3& other) const { return Vec3(this->x / other.x, this->y / other.y, this->z / other.z); }

template <typename T> Vec3<T> Vec3<T>::operator - () const { return Vec3(-this->x, -this->y, -this->z); }

template <typename T> Vec3<T>& Vec3<T>::operator += (const Vec3& other) { this->x += other.x; this->y += other.y; this->z += other.z; return *this; }
template <typename T> Vec3<T>& Vec3<T>::operator -= (const Vec3& other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; return *this; }
template <typename T> Vec3<T>& Vec3<T>::operator *= (const Vec3& other) { this->x *= other.x; this->y *= other.y; this->z *= other.z; return *this; }
template <typename T> Vec3<T>& Vec3<T>::operator /= (const Vec3& other) { this->x /= other.x; this->y /= other.y; this->z /= other.z; return *this; }

template <typename T> const Vec3<T>& Vec3<T>::unit()		{ static const Vec3 UNIT		= Vec3( 1,  1,  1); return UNIT;		}
template <typename T> const Vec3<T>& Vec3<T>::zero()		{ static const Vec3 ZERO		= Vec3( 0,  0,  0); return ZERO;		}
template <typename T> const Vec3<T>& Vec3<T>::one()			{ static const Vec3 ONE			= Vec3( 1,  1,  1); return ONE;			}
template <typename T> const Vec3<T>& Vec3<T>::left()		{ static const Vec3 LEFT		= Vec3(-1,  0,  0); return LEFT;		}
template <typename T> const Vec3<T>& Vec3<T>::right()		{ static const Vec3 RIGHT		= Vec3( 1,  0,  0); return RIGHT;		}
template <typename T> const Vec3<T>& Vec3<T>::up()			{ static const Vec3 UP			= Vec3( 0,  1,  0); return UP;			}
template <typename T> const Vec3<T>& Vec3<T>::down()		{ static const Vec3 DOWN		= Vec3( 0, -1,  0); return DOWN;		}
template <typename T> const Vec3<T>& Vec3<T>::forward()		{ static const Vec3 FORWARD		= Vec3( 0,  0,  1); return FORWARD;		}
template <typename T> const Vec3<T>& Vec3<T>::backward()	{ static const Vec3 BACKWARD	= Vec3( 0,  0, -1); return BACKWARD;	}

#endif // VEC3_H
