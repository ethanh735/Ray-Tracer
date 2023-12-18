#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

// General class used for vectors, points, colors, etc.
class vec3 {
public:
    double e[3];

    // constructors
    vec3() : e{0, 0, 0} {}
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    // getters
    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    // negative operator
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

    // subscript operators
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    // dot sum
    vec3& operator+=(const vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    // not dot product
    vec3& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    // why is this syntax so different from product?
    vec3& operator/=(double t) {
        return *this *= 1/t;
    }

    // different implementation from book
    double length() const {
        return sqrt(length_squared());
    }

    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
};

// just a vec3 alias, useful for geometric clarity in code
using point3 = vec3;

// Helper Utility Functions
// print output
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// sum initialization
inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0]+v.e[0], u.e[1]+v.e[1], u.e[2]+v.e[2]);
}

// difference initialization
inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0]-v.e[0], u.e[1]-v.e[1], u.e[2]-v.e[2]);
}

// product initialization
inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0]*v.e[0], u.e[1]*v.e[1], u.e[2]*v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}
inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

// different syntax for division
inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

// dot product
inline double dot(const vec3& u, const vec3& v) {
    return u.e[0]*v.e[0] + u.e[1]*v.e[1] + u.e[2]*v.e[2];
}

// cross product
inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1]*v.e[2] - u.e[2]*v.e[1], u.e[2]*v.e[0] - u.e[0]*v.e[2], u.e[0]*v.e[1] - u.e[1]*v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

#endif //VEC3_H