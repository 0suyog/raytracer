#pragma once
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

  double X() const { return v[0]; }
  double Y() const { return v[1]; }
  double Z() const { return v[2]; }

  double length_squared() const {
    return (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
  }
  double length() const { return std::sqrt(length_squared()); }

  double operator[](int i) const { return v[i]; }
  double &operator[](int i) { return v[i]; }

  vec3 &operator+=(double x) {
    v[0] += x;
    v[1] += x;
    v[2] += x;
    return *this;
  }

  vec3 &operator+=(const vec3 u) {
    v[0] += u.X();
    v[1] += u.Y();
    v[2] += u.Z();
    return *this;
  }

  vec3 &operator-=(double x) {
    v[0] -= x;
    v[1] -= x;
    v[2] -= x;
    return *this;
  }
  vec3 &operator-=(const vec3 u) {
    v[0] -= u.X();
    v[1] -= u.Y();
    v[2] -= u.Z();
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
  return out << v.X() << " " << v.Y() << " " << v.Z();
}
inline vec3 operator+(const vec3 &u, const vec3 &v) {
  return vec3(v.X() + u.X(), v.Y() + u.Y(), v.Z() + u.Z());
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
  return vec3(v.X() - u.X(), v.Y() - u.Y(), v.Z() - u.Z());
}

inline vec3 operator*(double x, const vec3 &v) {
  return vec3(v.X() * x, v.Y() * x, v.Z() * x);
}

inline vec3 operator*(const vec3 &v, double x) { return x * v; }

inline vec3 operator/(const vec3 &v, double x) { return v * (1 / x); }

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
