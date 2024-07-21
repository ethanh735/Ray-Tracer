#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

int main() {

    // Environment Setup
    hittable_list world;

    // Material Generation
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));                   // greenish
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));                   // mild blue
    // If a shallow ray is fired at glass, it is reflected.
    // If a relatively straight-on ray is fired, it is refracted, with theta prime (refracted angle) being greater than theta (incident angle).
    auto material_left   = make_shared<dielectric>(1.50);                                         // glass
    auto material_bubble = make_shared<dielectric>(1.00 / 1.50);                                  // air bubble in glass
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);                  // fairly fuzzy gold

    // Sphere Generation
    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));     // plane sphere
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));     // new center sphere
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));       // glass sphere
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.4, material_bubble));     // air bubble sphere
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));      // gold metal sphere

    // Camera Initialization, Ray Tracing, Rendering
    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.render(world);

    return 0;
}