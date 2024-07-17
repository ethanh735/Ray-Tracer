#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

#include "hittable.h"
#include "material.h"

class camera {
public:
    // default values
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int samples_per_pixel = 10;
    int max_depth = 10;             // number of ray bounces into scene: maximum returns no light value

    // renders image pixel by pixel
    void render(const hittable& world) {
        initialize();

        // ASCII color type, columns, rows, max color
        std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

        // Image Rendering
        for (int row = 0; row < image_height; ++row) {
            // Progress indicator
            std::clog << "\rScanlines Remaining: " << (image_height - row) << " " << std::flush;
            for (int col = 0; col < image_width; ++col) {
                color pixel_color(0,0,0);
                // cast multiple rays per pixel, getting a slightly different sample surrounding pixel each time
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    // fire ray, allowing certain number of surface reflections
                    ray r = get_ray(col, row);
                    // total the sample rays collected
                    pixel_color += ray_color(r, max_depth, world);
                }
                // divide total sampling by the number of samples
                write_color(std::cout, pixel_samples_scale * pixel_color);
            }
        }
        // enough blank space to clear out previous message
        std::clog << "\rDone.                 \n";
    }

private:
    int    image_height;         // Rendered image height
    double pixel_samples_scale;  // Color scale factor for a sum of pixel samples
    point3 center;               // Camera center
    point3 pixel00_loc;          // Location of pixel 0, 0
    vec3   pixel_delta_u;        // Offset to pixel to the right
    vec3   pixel_delta_v;        // Offset to pixel below

    void initialize() {
        // Given width and aspect ratio, calculate image height (at least 1)
        image_height = int(image_width / aspect_ratio);
        if (image_height < 1) { image_height = 1; }

        // pixels per sample
        pixel_samples_scale = 1.0 / samples_per_pixel;

        // Viewport Calculation:
        auto focal_length = 1.0;                                                            // distance between viewport and camera center
        auto viewport_height = 2.0;                                                         // arbitrary
        auto viewport_width = viewport_height * (double(image_width)/image_height);         // recalculation of aspect ratio based on approximated values: both image width and height are ints, division result must be double

        auto center = point3(0, 0, 0);                                                  // zeroed for simplicity

        // Calculate vectors across viewport edges: viewport size per edge
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // Vectors of distance between adjacent pixels: pixel size per edge
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the absolute location of the upper left pixel: {0,0,0} - {0,0,1} is viewport, over and up to corner
        auto viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        // offset to center ray within viewport pixel: 1/2 pixel size over and down
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    // Construct a camera ray originating from the origin and directed at randomly sample point around the pixel location i, j.
    ray get_ray(int i, int j) const {
        // generates a sample within a square of size -0.5,0.5
        auto offset = sample_square();
        // current pixel placement on viewport relative to offset top left corner, considering slight offset
        auto pixel_sample = pixel00_loc
                            + ((i + offset.x()) * pixel_delta_u)
                            + ((j + offset.y()) * pixel_delta_v);

        // exacting vector between current viewport position and camera
        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;

        // cast ray
        return ray(ray_origin, ray_direction);
    }

    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
    vec3 sample_square() const {
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    // Given ray position, calculate color of each pixel across screen
    color ray_color(const ray& r, int depth, const hittable& world) const {
        // If we've exceeded the ray bounce limit, no more light is gathered.
        if (depth <= 0)
            return color(0,0,0);

        hit_record rec;

        // for given hittable, if hit (according to what hittable is), reflect ray randomly and return what color is kept by recursive reflection
        if (world.hit(r, interval(0.001, infinity), rec)) {
            ray scattered;
            color attenuation;
            // returns using different behaviors depending on material
            if (rec.mat->scatter(r, rec, attenuation, scattered))
                // depth # of times, fire ray from hittable (previous hit point) in direction (from hemisphere) according to material
                return attenuation * ray_color(scattered, depth-1, world);
            return color(0,0,0);
        }

        // blue to white background lerp:
        // normalized value of calculated ray direction between camera and viewport intersection: 1, -1, or 0
        vec3 unit_direction = unit_vector(r.direction());

        // unit vector normalized to 0.0 <= a <= 1.0: higher y value for viewport intersection -> higher a
        auto a = 0.5 * (unit_direction.y() + 1.0);
        // lerp between blue and white: (1-a)*start + a*end
        return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }
};

#endif