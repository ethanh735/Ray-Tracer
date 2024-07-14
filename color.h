#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"

using color = vec3;

// gamma correction: gamma is sqrt(linear), linear is gamma^2 (approximately, for all RGB values)
inline double linear_to_gamma(double linear_component) {
    if (linear_component > 0) {
        return sqrt(linear_component);
    }
    return 0;
}

// using vec3, write color RGB value per pixel to screen, converted from 0.0-1.0 to 0-255
void write_color(std::ostream& out, const color& pixel_color) {
    // instead of color 0,1 multiplied by something just short of 256, color 0,0.999 multiplied by 256 exactly (no rgb value can be entirely present)
    interval intensity(0.000, 0.999);
    // now gamma corrected
    int r_byte = int(256 * intensity.clamp(linear_to_gamma(pixel_color.x())));
    int g_byte = int(256 * intensity.clamp(linear_to_gamma(pixel_color.y())));
    int b_byte = int(256 * intensity.clamp(linear_to_gamma(pixel_color.z())));

    out << r_byte << " " << g_byte << " " << b_byte << "\n";
}

#endif //COLOR_H