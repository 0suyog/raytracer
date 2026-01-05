#pragma once

#include "interval.h"
#include "ray.h"
#include "vec3.h"
class hit_record {
public:
  double t;
  point3 p;
  vec3 normal;

  hit_record() = default;
  ~hit_record() = default;
  void set_normal_face(const ray &r, const vec3 &n) {
    if (dot(r.direction(), n) < 0) {
      normal = -n;
    }
    normal = n;
  }
};

class hittable {
public:
  virtual ~hittable() = default;
  virtual bool hit(const ray &r, hit_record &h_rec,
                   const interval &ray_int) const = 0;
};
