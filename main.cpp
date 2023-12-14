#include <iostream>

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
            // r increases left to right, green increases top to bottom: ratio from 0.0-1.0
            float r = double(col) / (image_width-1);
            float g = double(row) / (image_height-1);
            float b = 0;

            // essentially rounding to nearest int 0-255
            int ir = int(r * 255);
            int ig = int(g * 255);
            int ib = int(b * 255);

            std::cout << ir << " " << ig << " " << ib << '\n';
        }
    }
    std::clog << "\rDone.\n";

    return 0;
}
