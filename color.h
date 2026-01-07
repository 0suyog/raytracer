#pragma once

#include "interval.h"
#include "vec3.h"
#include <cmath>
#include <iostream>
#include <ostream>
using color = vec3;

inline double linear_to_gamma(double linear_component) {
  if (linear_component > 0) {
    return std::sqrt(linear_component);
  }
  return 0;
}

inline void write_color(std::ostream &out, color pixel_color) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  interval intensity(0.000, 0.999);

  r = linear_to_gamma(r);
  g = linear_to_gamma(g);
  b = linear_to_gamma(b);

  auto rbyte = int(256 * intensity.clamp(r));
  auto gbyte = int(256 * intensity.clamp(g));
  auto bbyte = int(256 * intensity.clamp(b));

  out << rbyte << " " << gbyte << " " << bbyte << " ";
}

inline color mapped_color(double x, double y, double z) {
  return vec3(x / 255, y / 255, z / 255);
}
