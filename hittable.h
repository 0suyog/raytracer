#pragma once

#include "ray.h"
#include "vec3.h"
class hit_record {
public:
  double t;
  double p;
  vec3 normal;

  hit_record() = default;
  ~hit_record() = default;
};

class hittable {
public:
  virtual ~hittable() = default;
  virtual bool hit(const ray &r, hit_record &h_rec) const = 0;
};
