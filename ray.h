#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
    // constructors
    ray() {}
    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    point3 origin() const { return orig; }
    vec3 direction() const { return dir; }

    // P(t) = A + tb, where P is a point t distance away from origin point A (direction b)
    point3 at(double t) const {
        return orig + t*dir;
    }

private:
    point3 orig;
    vec3 dir;
};

#endif //RAY_H