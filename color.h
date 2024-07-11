#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"

using color = vec3;

// using vec3, write color RGB value per pixel to screen, converted from 0.0-1.0 to 0-255
void write_color(std::ostream& out, const color& pixel_color) {
    // instead of color 0,1 multiplied by something just short of 256, color 0,0.999 multiplied by 256 exactly (no rgb value can be entirely present)
    interval intensity(0.000, 0.999);
    int r_byte = int(256 * intensity.clamp(pixel_color.x()));
    int g_byte = int(256 * intensity.clamp(pixel_color.y()));
    int b_byte = int(256 * intensity.clamp(pixel_color.z()));

    out << r_byte << " " << g_byte << " " << b_byte << "\n";
}

#endif //COLOR_H