#pragma once

#include "constants.h"
#include <ostream>
class interval {
public:
  double min;
  double max;
  interval() : min(-infinity), max(infinity) {}
  interval(double min, double max) : min(min), max(max) {};
  bool contains(double value) const { return (min <= value && value <= max); }
  bool surrounds(double value) const { return (min < value && value < max); }
  double clamp(double value) const {
    if (value < min) {
      return min;
    }
    if (value > max) {
      return max;
    }
    return value;
  }
  double size() const { return max - min; }
};

inline std::ostream &operator<<(std::ostream &out, const interval &i) {
  return out << "max: " << i.max << "min: " << i.min;
}
