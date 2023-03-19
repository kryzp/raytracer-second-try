#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>
#include <limits>
#include <memory>
#include <vector>
#include <random>

template <typename T>
using Vector = std::vector<T>;

template <typename T>
using Unique = std::unique_ptr<T>;
template <typename T, typename... TArgs>
constexpr Unique<T> create_scope(TArgs&&... args) { return std::make_unique<T>(std::forward<TArgs>(args)...); }

template <typename T>
using Ref = std::shared_ptr<T>;
template <typename T, typename... TArgs>
constexpr Ref<T> create_ref(TArgs&&... args) { return std::make_shared<T>(std::forward<TArgs>(args)...); }

template <typename T>
using Weak = std::weak_ptr<T>;

constexpr double INF = std::numeric_limits<double>::infinity();
#define PI 3.1415926535897932385;
#define DEG2RAD 0.0174532925199
#define RAD2DEG 57.2957795131

double randd();
double randd(double mn, double mx);

#endif // CONSTANTS_H
