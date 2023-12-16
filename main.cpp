#include <iostream>

#include "color.h"
#include "vec3.h"

int main() {

    int image_width = 256;
    int image_height = 256;

    // ASCII color type, columns, rows, max color
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    // Image Rendering
    for (int row = 0; row < image_height; ++row) {
        // Progress bar
        std::clog << "\rScanlines Remaining: " << (image_height - row) << " " << std::flush;
        for (int col = 0; col < image_width; ++col) {
            // r increases left to right, g increases top to bottom: ratio of current place to image size
            auto pixel_color = color(double(col)/(image_width-1), double(row)/(image_height-1), 0);

            write_color(std::cout, pixel_color);
        }
    }
    // enough blank space to clear out previous message
    std::clog << "\rDone.                 \n";

    return 0;
}