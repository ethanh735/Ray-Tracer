#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

using color = vec3;

// using vec3, write color RGB value per pixel to screen, converted from 0.0-1.0 to 0-255
void write_color(std::ostream& out, color pixel_color) {
    out << int(255.999*pixel_color.x()) << " " << int(255.999*pixel_color.y()) << " " << int(255.999*pixel_color.z()) << "\n";
}

#endif //COLOR_H