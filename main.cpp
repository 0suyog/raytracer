#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"
#include "vec3.h"
#include <memory>

int main() {
  camera c;
  hittable_list world;

  world.add(std::make_shared<sphere>(0.5, point3(0, 0, -1)));
  world.add(std::make_shared<sphere>(100, point3(0, -100.5, -1)));

  c.no_of_pixel_samples = 100;
  c.render(world);
}
