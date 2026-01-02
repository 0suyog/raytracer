#pragma once
#include "hittable.h"
#include "vec3.h"
#include <cmath>
class sphere : public hittable {
private:
  double radius = 7;
  point3 center = point3(0, 0, -10);

public:
  sphere(double radius, point3 &center) : radius(radius), center(center) {}
  bool hit(const ray &r, hit_record &hit_rec) const override {

    auto a = 1;
    auto co = center - r.origin();
    auto d = r.direction();
    auto h = dot(d, co);
    auto c = (dot(co, co)) - (radius * radius);

    auto discriminant = (h * h) - (a * c);

    if (discriminant < 0) {
      return false;
    }

    auto sqrt_disc = sqrt(discriminant);
    // currently checking for only nearest hit
    auto hit_point = (h - sqrt_disc) / a;
    hit_rec.p = hit_point;
    hit_rec.t = discriminant;

    return true;
  }
};
