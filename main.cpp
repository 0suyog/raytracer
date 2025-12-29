#include <iostream>
int main() {
  // defining image height and weight
  int image_height = 255;
  int image_width = 255;
  // P3 header width height and max color
  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
  for (int j = 0; j < image_height; j++) {
    for (int i = 0; i < image_width; i++) {
      std::cout << i << " " << 0 << " " << 0 << " ";
    }
    std::cout << "\n";
  }
}
