#include "color.h"
#include "ray.h"
#include "vec3.h"

// Given a sphere of some size and position, calculate ray intersections using quadratic formula
double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;                                  // camera center - sphere center: A - C
    auto a = r.direction().length_squared();                // b^2
    auto half_b = dot(oc, r.direction());             // b * (A - C)
    auto c = oc.length_squared() - radius*radius;           // (A - C)^2 - r^2
    // quadratic formula part under root: returns negative (no intersect), 0 (1 intersect), or positive (2 intersect)
    auto discriminant = half_b*half_b - 4*a*c;

    // normal calculation: returns where intersection is
    if (discriminant < 0) {
        return -1.0;
    }
    else {
        // full quadratic formula: negative side is entry point of sphere, positive part is exit point (for refraction)
        return (-half_b - sqrt(discriminant) ) / a;
    }
}

// Given ray position, calculate color of each pixel across screen
color ray_color(const ray& r) {
    // sphere intersections
    auto t = hit_sphere(point3(0,0,-1), 0.5, r);
    // if intersection, generate normal
    if (t > 0.0) {
        // P - C: normalized normal
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
        // arbitrary color map based on normal xyz
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }

    // blue to white background lerp:
    // normalized value of calculated ray direction between camera and viewport intersection: 1, -1, or 0
    vec3 unit_direction = unit_vector(r.direction());

    // unit vector normalized to 0.0 <= a <= 1.0: higher y value for viewport intersection -> higher a
    auto a = 0.5 * (unit_direction.y() + 1.0);
    // lerp between blue and white: (1-a)*start + a*end
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {

    // Given width and aspect ratio, calculate image height (at least 1)
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = (int)(image_width / aspect_ratio);

    if (image_height < 1) { image_height = 1; }

    // Viewport Calculation:
    auto focal_length = 1.0;                                                            // distance between viewport and camera center
    auto viewport_height = 2.0;                                                         // arbitrary
    auto viewport_width = viewport_height * ((double)(image_width)/image_height);       // recalculation of aspect ratio based on approximated values
    auto camera_center = point3(0, 0, 0);                                           // zeroed for simplicity

    // Calculate vectors across viewport edges: viewport size per edge
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Vectors of distance between adjacent pixels: pixel size per edge
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the absolute location of the upper left pixel: {0,0,0} - {0,0,1} is viewport, over and up to corner
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    // offset to center ray within viewport pixel: 1/2 pixel size over and down
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // ASCII color type, columns, rows, max color
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    // Image Rendering
    for (int row = 0; row < image_height; ++row) {
        // Progress indicator
        std::clog << "\rScanlines Remaining: " << (image_height - row) << " " << std::flush;
        for (int col = 0; col < image_width; ++col) {
            // current pixel placement on viewport relative to offset top left corner
            auto pixel_center = pixel00_loc + (col * pixel_delta_u) + (row * pixel_delta_v);
            // exacting vector between current viewport position and camera
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