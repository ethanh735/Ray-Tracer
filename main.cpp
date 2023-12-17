#include <iostream>

#include "color.h"
#include "ray.h"
#include "vec3.h"

// default is always black for now
color ray_color(const ray& r) {
    return color(0, 0, 0);
}

int main() {

    // Given width and aspect ratio, calculate image height (at least 1)
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = int(image_width / aspect_ratio);

    if (image_height < 1) { image_height = 1; }

    // Viewport Calculation:
    auto focal_length = 1.0;                                                        // distance between viewport and camera center
    auto viewport_height = 2.0;                                                     // arbitrary
    auto viewport_width = viewport_height * (double(image_width)/image_height);     // recalculation of aspect ratio based on approximated values
    auto camera_center = point3(0, 0, 0);                                       // zeroed for simplicity

    // Calculate the vectors across viewport edges
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Vectors of distance between adjacent pixels
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    // offset to center rays in viewport pixels
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // ASCII color type, columns, rows, max color
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    // Image Rendering
    for (int row = 0; row < image_height; ++row) {
        // Progress bar
        std::clog << "\rScanlines Remaining: " << (image_height - row) << " " << std::flush;
        for (int col = 0; col < image_width; ++col) {
            // r increases left to right, g increases top to bottom: ratio of current place to image size

            // current pixel placement relative to offset top left corner
            auto pixel_center = pixel00_loc + (row * pixel_delta_u) + (col * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;

            // cast ray
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    // enough blank space to clear out previous message
    std::clog << "\rDone.                 \n";

    return 0;
}