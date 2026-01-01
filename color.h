#pragma once

#include "vec3.h"
#include <ostream>
using color = vec3;

inline void write_color(std::ostream &out, color pixel_color) {
  int r = int(pixel_color.x() * 255.999);
  int g = int(pixel_color.y() * 255.999);
  int b = int(pixel_color.z() * 255.999);

  out << r << " " << g << " " << b << " ";
}
