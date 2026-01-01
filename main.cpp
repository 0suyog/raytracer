#include "color.h"
#include "ray.h"
#include "vec3.h"
#include <iostream>
#include <ostream>

bool hit_sphere(const ray &r) {
  double radius = 7;
  point3 center(0, 0, -10);
  auto a = 1;
  auto co = center - r.origin();
  auto d = r.direction();
  auto h = dot(d, co);
  auto c = (dot(co, co)) - (radius * radius);

  auto discriminant = (h * h) - c;

  return discriminant > 0;
}

color ray_color(const ray &r) {
  if (hit_sphere(r)) {
    return color(1, 0, 0);
  }
  vec3 direction = r.direction();
  auto a = 0.5 * (direction.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0, 0, 1.0);
}

int main() {
  // defining image height and weight
  auto aspect_ratio = double(16) / 9;
  int image_width = 720;
  int image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1 ? 1 : image_height);

  double focal_length = 1;
  point3 camera_center = point3(0, 0, 0);
  auto viewport_height = 2.0;
  auto viewport_width = viewport_height * (double(image_width) / image_height);

  // vec3 viewport_u_dir = vec3(1, 0, 0);
  // vec3 viewport_v_dir = vec3(0, -1, 0);
  // vec3 viewport_u = viewport_u_dir * viewport_width;
  // vec3 viewport_v = viewport_v_dir * viewport_height;
  auto viewport_u = vec3(viewport_width, 0, 0);
  vec3 viewport_v(0, -viewport_height, 0);

  vec3 pixel_delta_u = viewport_u / image_width;
  vec3 pixel_delta_v = viewport_v / image_height;
  // std::cerr << "\n" << pixel_delta_u << "\n" << pixel_delta_v << "\n";

  auto viewport_upperleft = camera_center - vec3(0, 0, focal_length) -
                            (viewport_u / 2) - (viewport_v / 2);
  point3 pixel00_loc =
      viewport_upperleft + 0.5 * (pixel_delta_u + pixel_delta_v);
  // P3 header width height and max color
  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
  for (int j = 0; j < image_height; j++) {
    std::clog << "\rScanlines remaining:" << image_height - j << std::flush;
    for (int i = 0; i < image_width; i++) {
      auto pixel_location =
          pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
      auto ray_direction = unit_vector(pixel_location - camera_center);
      auto r = ray(camera_center, ray_direction);
      write_color(std::cout, ray_color(r));
    }
    std::cout << "\n";
  }
  std::clog << "\rDone.                        \n" << std::flush;
}
