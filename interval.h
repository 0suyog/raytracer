#pragma once

#include "constants.h"
class interval {
public:
  double min;
  double max;
  interval() : min(-infinity), max(infinity) {}
  interval(double min, double max) : min(min), max(max) {};
};
