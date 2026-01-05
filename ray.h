#pragma once
#include "vec3.h"
class ray {
private:
  point3 orig;
  vec3 dir;

public:
  ray() = default;
  ray(point3 origin, vec3 direction) : orig(origin), dir(direction) {}
  ~ray() = default;

  const vec3 at(double point) const { return orig + (dir * point); }
  const vec3 &direction() const { return dir; }
  const point3 &origin() const { return orig; }
};
