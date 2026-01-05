#pragma once
#include "utils.h"
#include <cmath>
#include <ostream>
class vec3 {

public:
  double v[3] = {0, 0, 0};
  vec3() = default;
  vec3(double x, double y, double z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
  }
  ~vec3() = default;

  double x() const { return v[0]; }
  double y() const { return v[1]; }
  double z() const { return v[2]; }

  double length_squared() const {
    return (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
  }
  double length() const { return std::sqrt(length_squared()); }

  vec3 operator-() const { return vec3(-v[0], -v[1], -v[2]); }
  double operator[](int i) const { return v[i]; }
  double &operator[](int i) { return v[i]; }

  vec3 &operator+=(double x) {
    v[0] += x;
    v[1] += x;
    v[2] += x;
    return *this;
  }

  vec3 &operator+=(const vec3 u) {
    v[0] += u.x();
    v[1] += u.y();
    v[2] += u.z();
    return *this;
  }

  vec3 &operator-=(double x) {
    v[0] -= x;
    v[1] -= x;
    v[2] -= x;
    return *this;
  }
  vec3 &operator-=(const vec3 u) {
    v[0] -= u.x();
    v[1] -= u.y();
    v[2] -= u.z();
    return *this;
  }
  vec3 &operator*=(double x) {
    v[0] *= x;
    v[1] *= x;
    v[2] *= x;
    return *this;
  }
  vec3 &operator/=(double x) {
    v[0] /= x;
    v[1] /= x;
    v[2] /= x;
    return *this;
  }
};

using point3 = vec3;

inline std::ostream &operator<<(std::ostream &out, const vec3 &v) {
  return out << v.x() << " " << v.y() << " " << v.z();
}
inline vec3 operator+(const vec3 &v, const vec3 &u) {
  return vec3(v.x() + u.x(), v.y() + u.y(), v.z() + u.z());
}

inline vec3 operator+(const vec3 &v, double n) {
  return vec3(v.x() + n, v.y() + n, v.z() + n);
}

inline vec3 operator+(double n, const vec3 &v) { return v + n; }

inline vec3 operator-(const vec3 &v, double n) {
  return vec3(v.x() - n, v.y() - n, v.z() - n);
}

inline vec3 operator-(double n, const vec3 &v) { return v - n; }

inline vec3 operator-(const vec3 &v, const vec3 &u) {
  return vec3(v.x() - u.x(), v.y() - u.y(), v.z() - u.z());
}

inline vec3 operator*(double x, const vec3 &v) {
  return vec3(v.x() * x, v.y() * x, v.z() * x);
}

inline vec3 operator*(const vec3 &v, double x) { return x * v; }

inline vec3 operator/(const vec3 &v, double x) { return v * (1.0 / x); }

inline double dot(const vec3 &v1, const vec3 &v2) {
  auto d = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
  return d;
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
  return vec3(u.v[1] * v.v[2] - u.v[2] * v.v[1],
              u.v[2] * v.v[0] - u.v[0] * v.v[2],
              u.v[0] * v.v[1] - u.v[1] * v.v[0]);
}

inline vec3 unit_vector(const vec3 &v) { return v / v.length(); }

inline vec3 random_vector() {
  return vec3(random_double(), random_double(), random_double());
}

inline vec3 random_unit_vector() {
  while (true) {
    auto vec = random_vector();
    auto len_sq = vec.length_squared();
    if (1e-160 < len_sq && len_sq <= 1) {
      return unit_vector(vec);
    }
  }
}

inline vec3 random_on_hemisphere(const vec3 normal) {
  auto vec = random_unit_vector();
  return dot(vec, normal) > 0 ? vec : -vec;
}
