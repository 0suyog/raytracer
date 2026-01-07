#pragma once

#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "utils.h"
#include "vec3.h"
#include <cmath>
#include <iostream>

class camera {
private:
  int image_height;
  double viewport_width;
  vec3 viewport_u, viewport_v, pixel_delta_u, pixel_delta_v, viewport_upperleft;
  point3 pixel00_loc;
  double viewport_height;

  void initialize() {
    image_height = image_width / aspect_ratio;
    image_height = image_height < 1 ? 1 : image_height;
    viewport_height = 2 * tan(degrees_to_radians(vfov / 2)) * -focal_length;
    viewport_width = viewport_height * (double(image_width) / image_height);
    viewport_u = vec3(viewport_width, 0, 0);
    viewport_v = vec3(0, -viewport_height, 0);

    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;
    viewport_upperleft = camera_center - vec3(0, 0, focal_length) -
                         (viewport_u / 2) - (viewport_v / 2);
    pixel00_loc = viewport_upperleft + 0.5 * (pixel_delta_u + pixel_delta_v);
  }

  color ray_color(const ray &r, hittable_list world, int bounces) {
    if (bounces <= 0) {
      return color(0, 0, 0);
    }
    auto h_rec = hit_record();
    interval ray_int(0.001, infinity);
    if (world.hit(r, h_rec, ray_int)) {
      color attenuation;
      vec3 scattered_direction;
      if (h_rec.mat->scatter(r, h_rec, attenuation, scattered_direction)) {
        auto r = ray(h_rec.p, scattered_direction);
        return attenuation * ray_color(r, world, bounces - 1);
      }
      return color(0, 0, 0);
    }
    vec3 direction = unit_vector(r.direction());
    auto a = 0.5 * (direction.y() + 1.0);
    // return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0, 0, 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
  }

  ray get_ray(int i, int j) const {
    auto offset = sample_offset();
    auto pixel_location = pixel00_loc + ((i + offset.x()) * pixel_delta_u) +
                          ((j + offset.y()) * pixel_delta_v);
    // pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v) + offset;
    auto ray_direction = pixel_location - camera_center;
    auto r = ray(camera_center, ray_direction);
    return r;
  }

  vec3 sample_offset() const {
    return vec3(random_double() - 0.5, random_double() - 0.5, 0);
  }

public:
  double aspect_ratio = double(16) / 9;
  int image_width = 720;
  double focal_length = 1;
  point3 camera_center = point3(0, 0, 0);
  int max_bounces = 10;
  int samples_per_pixel = 10;
  double vfov = 80;
  vec3 vup = vec3(0, 1, 0);

  void render(const hittable_list &world) {
    initialize();
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for (int j = 0; j < image_height; j++) {
      std::clog << "\rScanlines remaining:" << image_height - j << std::flush;
      for (int i = 0; i < image_width; i++) {
        color c(0, 0, 0);
        for (int s = 0; s < samples_per_pixel; s++) {
          auto r = get_ray(i, j);
          c += ray_color(r, world, max_bounces);
        }
        auto avg_clr = c / samples_per_pixel;
        write_color(std::cout, avg_clr);
      }
      std::cout << "\n";
    }
    std::clog << "\rDone.                        \n" << std::flush;
  }
};
