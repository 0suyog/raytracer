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
    scatter_direction = unit_vector(reflect(r.direction(), h_rec.normal)) +
                        (random_unit_vector() * fuzz);
    return true;
  }
};

class dielectric : public material {
private:
  color albedo;
  /// refractive index
  double refraction_index;

  static double reflectance(double cosine, double refraction_index) {
    // schlick approximation
    auto r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow(1 - cosine, 5);
  }

public:
  dielectric(const color &albedo, double refraction_index)
      : albedo(albedo), refraction_index(refraction_index) {}
  bool scatter(const ray &r, const hit_record &h_rec, color &attenuation,
               vec3 &scatter_direction) const override {
    attenuation = albedo;
    auto ri = 1 / refraction_index;
    if (!h_rec.isFrontFace) {
      ri = refraction_index;
    }
    auto unit_direction = unit_vector(r.direction());
    auto cos_theta = fmin(dot(-unit_direction, h_rec.normal), 1);
    auto sin_theta = std::sqrt(1 - (cos_theta * cos_theta));
    vec3 direction;
    bool should_total_internal_reflect = ri * sin_theta > 1;
    if (should_total_internal_reflect) {
      direction = reflect(unit_direction, h_rec.normal);
    } else {
      direction = refract(unit_direction, h_rec.normal, ri);
    }
    scatter_direction = direction;
    return true;
  }
};
