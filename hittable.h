#pragma once

#include "ray.h"
#include "vec3.h"
class hit_record {
public:
  double t;
  double p;
  vec3 normal;
};

class hittable {
  virtual bool hit(const ray &r, hit_record &h_rec);
};
