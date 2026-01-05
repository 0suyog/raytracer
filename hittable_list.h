#pragma once

#include "hittable.h"
#include "interval.h"
#include <iostream>
#include <memory>
#include <vector>
class hittable_list : public hittable {
private:
  std::vector<std::shared_ptr<hittable>> world;

public:
  hittable_list() = default;
  hittable_list(const std::shared_ptr<hittable> h) { add(h); }
  void add(const std::shared_ptr<hittable> h) { world.push_back(h); }
  bool hit(const ray &r, hit_record &h_rec,
           const interval &ray_int) const override {
    auto closest_so_far = ray_int.max;
    auto hit_anything = false;
    auto temp_int = interval(ray_int);
    for (auto obj : world) {
      if (obj->hit(r, h_rec, temp_int)) {
        hit_anything = true;
        closest_so_far = h_rec.t;
        temp_int.max = closest_so_far;
      }
    }
    return hit_anything;
  }
};
