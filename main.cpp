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
  auto material_left = make_shared<dielectric>(color(1, 1, 1), 1.50);
  auto material_bubble = make_shared<dielectric>(color(1, 1, 1), 1.00 / 1.50);
  auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);
  world.add(
      make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(make_shared<sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
  world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
  world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.4, material_bubble));
  world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

  c.aspect_ratio = 16.0 / 9;
  c.image_width = 400;
  c.samples_per_pixel = 10;
  c.max_bounces = 10;
  c.vfov = 40;
  c.lookfrom = point3(-1.5, 0, 1);
  c.lookat = point3(0, 0, -1);
  c.vup = vec3(0, 1, 0);
  c.render(world);
}
