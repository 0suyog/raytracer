#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "vec3.h"
#include <memory>
using std::make_shared;

int main() {
  camera c;
  hittable_list world;
  auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
  auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
  auto material_left = make_shared<metal>(color(0.2, 0.8, 0), 0);
  auto material_right = make_shared<metal>(color(0.8, 0.2, 0), 0);
  // world.add(
  //     make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0,
  //     material_ground));
  // world.add(make_shared<sphere>(point3(0.0, 0.0, -1.2), 0.5,
  // material_center)); world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0),
  // 0.5, material_left)); world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0),
  // 0.5, material_right));

  world.add(make_shared<sphere>(point3(0.50001, 0, -1.2), 0.5, material_left));
  world.add(make_shared<sphere>(point3(-0.5001, 0, -1.2), 0.5, material_right));

  c.aspect_ratio = 16.0 / 9;
  c.image_width = 400;
  c.samples_per_pixel = 100;
  c.max_bounces = 100;
  c.vfov = 60;
  c.render(world);
}
