#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

int main() {

    // Environment Setup
    hittable_list world;

    auto R = cos(pi/4);

    // Material Generation
    auto material_left  = make_shared<lambertian>(color(0,0,1));    // blue
    auto material_right = make_shared<lambertian>(color(1,0,0));    // red

    // Sphere Generation
    world.add(make_shared<sphere>(point3(-R, 0, -1), R, material_left));
    world.add(make_shared<sphere>(point3( R, 0, -1), R, material_right));

    // Camera Initialization, Ray Tracing, Rendering
    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.v_fov = 90;

    cam.render(world);

    return 0;
}