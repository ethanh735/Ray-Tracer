#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
    // constructor
    sphere(point3 _center, double _radius) : center(_center), radius(_radius) {}

    // defines ray intersection function according to quadratic formula
    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
        // quadratic formula components
        vec3 oc = r.origin() - center;
        auto a = r.direction().length_squared();
        auto half_b = dot(oc, r.direction());
        auto c = oc.length_squared() - radius*radius;

        // sqrt(4) = 2, equation has been /2, so b^2 - ac
        auto discriminant = half_b*half_b - a*c;
        if (discriminant < 0) return false;

        auto sqrtd = sqrt(discriminant);

        // half of quadratic formula: simplifies multiplication slightly by removing factor
        // negative side (ray entry point)
        auto root = (-half_b - sqrtd) / a;

        // find the nearest root that lies in the t-value range
        if (root <= ray_tmin || ray_tmax <= root) {
            root = (-half_b + sqrtd) / a;
            // check positive side (ray exit point) after negative
            if (root <= ray_tmin || ray_tmax <= root) {
                return false;
            }
        }

        // passing hit information to hit record
        rec.t = root;
        rec.p = r.at(rec.t);
        // set normal, flip if at exit point
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }

private:
    point3 center;
    double radius;
};

#endif //SPHERE_H