#pragma once
#include "hittable.h"
#include "interval.h"
#include "vec3.h"
#include <cmath>
class sphere : public hittable {
private:
  double radius = 7;
  point3 center = point3(0, 0, -10);

public:
  sphere() = default;
  sphere(double radius, const point3 &center)
      : radius(radius), center(center) {}
  bool hit(const ray &r, hit_record &hit_rec,
           const interval &ray_int) const override {

    auto a = 1;
    auto co = center - r.origin();
    auto d = r.direction();
    auto h = dot(d, co);
    auto c = (dot(co, co)) - (radius * radius);

    auto discriminant = (h * h) - (a * c);

    if (discriminant <= 0) {
      return false;
    }

    // currently checking for only nearest hit
    auto sqrt_disc = sqrt(discriminant);
    auto t = (h - sqrt_disc) / a;
    if (!ray_int.surrounds(t)) {
      t = (h + sqrt_disc) / a;
      if (!ray_int.surrounds(t)) {
        return false;
      }
    }
    hit_rec.p = r.at(t);
    hit_rec.t = t;
    hit_rec.set_normal_face(r, normal(hit_rec.p));

    return true;
  }

  vec3 normal(const point3 p) const { return unit_vector(p - center); }
};
