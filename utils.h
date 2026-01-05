#pragma once

#include "constants.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

inline double map(double value, double tomin, double tomax) {
  return value * tomin + (tomax - tomin);
}

inline double map(double value, double from_min, double from_max, double to_min,
                  double to_max) {
  // mapping to 0-1
  auto val = (value - (from_max - from_min)) / from_min;
  return map(val, to_min, to_max);
}

inline double random_double() { return std::rand() / (RAND_MAX + 1.0); }

inline double random_double(double min, double max) {
  return map(random_double(), min, max);
}

inline double degrees_to_radians(double deg) { return deg * (pi / 180); }

inline auto make_normal_distributor(double sigma) {
  return [sigma](double x) {
    // auto x = random_double();
    return (1 / (sqrt(2 * pi * sigma * sigma)) *
            (exp(-((x * x) / (2 * sigma * sigma)))));
  };
}

template <typename T> inline void Log(T a) { std::cerr << "\n" << a << "\n"; };
