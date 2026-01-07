#pragma once

#include "interval.h"
#include "ray.h"
#include "vec3.h"
#include <memory>

class material;

class hit_record {
public:
  double t;
  point3 p;
  vec3 normal;
  bool isFrontFace = true;
  std::shared_ptr<material> mat;

  hit_record() = default;
  ~hit_record() = default;
  void set_front_normal(const ray &r, const vec3 &n) {
    isFrontFace = true;
    normal = n;
    if (dot(r.direction(), n) >= 0) {
      isFrontFace = false;
      normal = -n;
    }
  }
};

class hittable {
public:
  virtual ~hittable() = default;
  virtual bool hit(const ray &r, hit_record &h_rec,
                   const interval &ray_int) const = 0;
};
