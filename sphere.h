#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
    // Stationary Sphere constructor
    sphere(const point3& static_center, double radius, shared_ptr<material> mat) : center(static_center, vec3(0,0,0)), radius(std::fmax(0,radius)), mat(mat) {}
    // Moving Sphere constructor
    sphere(const point3& center1, const point3& center2, double radius, shared_ptr<material> mat) : center(center1, center2 - center1), radius(std::fmax(0,radius)), mat(mat) {}

    // defines ray intersection function according to quadratic formula
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        // quadratic formula components, modified to consider when ray hits sphere during frame time
        point3 current_center = center.at(r.time());
        vec3 oc = current_center - r.origin();                          // sphere center - camera center: A - C
        auto a = r.direction().length_squared();                // b^2
        auto half_b = dot(r.direction(), oc);             // b * (A - C)
        auto c = oc.length_squared() - radius*radius;           // (A - C)^2 - r^2

        // quadratic formula part under root: returns negative (no intersect), 0 (1 intersect), or positive (2 intersect)
        // sqrt(4) = 2, equation has been /2, so b^2 - ac
        auto discriminant = half_b*half_b - a*c;
        if (discriminant < 0) return false;

        auto sqrt_d = sqrt(discriminant);

        // half of quadratic formula: simplifies multiplication slightly by removing factor
        // negative side (ray entry point)
        auto root = (half_b - sqrt_d) / a;

        // find the nearest root that lies in the t-value range
        if (!ray_t.surrounds(root)) {
            root = (half_b + sqrt_d) / a;
            // check positive side (ray exit point) after negative
            if (!ray_t.surrounds(root)) {
                return false;
            }
        }

        // passing hit information to hit record
        rec.t = root;
        rec.p = r.at(rec.t);
        rec.mat = mat;
        // set normal at sphere (wherever it is in time of frame), flip if at exit point
        vec3 outward_normal = (rec.p - current_center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }

private:
    ray center;             // ray from starting center to ending center (for movement): static spheres move from 0 to 0
    double radius;
    shared_ptr<material> mat;
};

#endif //SPHERE_H