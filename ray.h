#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
    // constructors
    ray() {}
    // initializer lists
    ray(const point3& origin, const vec3& direction, double time) : orig(origin), dir(direction), tm(time) {}
    ray(const point3& origin, const vec3& direction) : ray(origin, direction, 0) {}

    // getters
    point3 origin() const { return orig; }
    vec3 direction() const { return dir; }
    double time() const { return tm; }

    // P(t) = A + tb, where P is a point t distance away from origin point A (direction b)
    point3 at(double t) const {
        return orig + t*dir;
    }

private:
    point3 orig;
    vec3 dir;
    double tm;
};

#endif //RAY_H