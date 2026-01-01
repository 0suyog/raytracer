#pragma once
#include "hittable.h"
#include "vec3.h"
class sphere : public hittable {
private:
  double radius = 7;
  point3 center = point3(0, 0, -10);
  sphere() = default;
  sphere(double radius, point3 &center) : radius(radius), center(center) {}

  bool hit(const ray &r, hit_record &hit_rec) override {

    auto a = 1;
    auto co = center - r.origin();
    auto d = r.direction();
    auto h = dot(d, co);
    auto c = (dot(co, co)) - (radius * radius);

    auto discriminant = (h * h) - c;

    return discriminant > 0;
  }
};
