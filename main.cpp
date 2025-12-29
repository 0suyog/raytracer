#include <iostream>
int main() {
  // defining image height and weight
  int image_height = 255;
  int image_width = 255;
  // P3 header width height and max color
  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
  for (int j = 0; j <= image_height; j++) {
    for (int i = 0; i <= image_width; i++) {
      auto r = double(i) / (image_width - 1);
      auto g = double(j) / (image_height - 1);
      auto b = 0;

      int scaledr = int(r * 255.999);
      int scaledb = int(g * 255.999);
      int scaledg = int(b * 255.999);

      std::cout << scaledr << " " << scaledg << " " << scaledb << " ";
    }
    std::cout << "\n";
  }
}
