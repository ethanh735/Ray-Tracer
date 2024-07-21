#ifndef VEC3_H
#define VEC3_H

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

    double length() const {
        return sqrt(length_squared());
    }

    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    // Return true if the vector is close to zero in all dimensions.
    bool near_zero() const {
        auto s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }

    // random vector generations for surface reflection
    static vec3 random() {
        return vec3(random_double(), random_double(), random_double());
    }

    static vec3 random(double min, double max) {
        return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
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

inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

// dot product
inline double dot(const vec3& u, const vec3& v) {
    return u.e[0]*v.e[0]
        + u.e[1]*v.e[1]
        + u.e[2]*v.e[2];
}

// cross product
inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1]*v.e[2] - u.e[2]*v.e[1],
                u.e[2]*v.e[0] - u.e[0]*v.e[2],
                u.e[0]*v.e[1] - u.e[1]*v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

// generates random vectors until one lands within unit sphere (sphere drawn within -1,1 unit cube)
inline vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1,1);
        if (p.length_squared() < 1)
            return p;
    }
}

// unit sphere vector normalized to unit length
inline vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

// dot product between unit sphere vector and surface normal to determine whether unit sphere vector is on, or needs to be flipped to, correct hemisphere
inline vec3 random_on_hemisphere(const vec3& normal) {
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0)          // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

// Given incident ray and normal, return v * 2b (exactly reflected ray for metals)
inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n)*n;        // v - 2b * n
}

// Snell's Law: refracted ray split into parallel and perpendicular parts & calculated to get sin(𝜃′), the angle between refracted ray and normal of refraction surface
inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

#endif //VEC3_H