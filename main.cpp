#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

int main() {

    // Environment Setup
    hittable_list world;

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));        // rgb sphere
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));   // plane sphere

    // Camera Initialization, Ray Tracing, Rendering
    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 400;

    cam.render(world);

    return 0;
}