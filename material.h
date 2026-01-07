#pragma once

#include "color.h"
#include "hittable.h"
#include "ray.h"
#include "vec3.h"

class material {
public:
  material() = default;
  ~material() = default;
  virtual bool scatter(const ray &r, const hit_record &h_rec,
                       color &attenuation, vec3 &scatter_direction) const {
    return false;
  }
};

class lambertian : public material {
private:
  color albedo;

public:
  lambertian(color a) : albedo(a) {}
  bool scatter(const ray &r, const hit_record &h_rec, color &attenuation,
               vec3 &scatter_direction) const override {
    attenuation = this->albedo;
    // auto direction = random_on_hemisphere(h_rec.normal);
    auto direction = h_rec.normal + random_unit_vector();
    if (near_zero(direction)) {
      scatter_direction = h_rec.normal;
    } else {
      scatter_direction = direction;
    }
    return true;
  }
};

class metal : public material {
private:
  color albedo;
  double fuzz;

public:
  metal(color a, double fuzz) : albedo(a), fuzz(fuzz) {}
  bool scatter(const ray &r, const hit_record &h_rec, color &attenuation,
               vec3 &scatter_direction) const override {
    attenuation = albedo;
    scatter_direction =
        reflect(r.direction(), h_rec.normal) + (random_unit_vector() * fuzz);
    return true;
  }
};
