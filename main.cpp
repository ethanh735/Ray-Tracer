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
    auto material_left   = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);                   // slightly fuzzy silver
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);                   // fairly fuzzy gold

    // Sphere Generation
    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));     // plane sphere
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));     // new center sphere
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));       // silver metal sphere
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