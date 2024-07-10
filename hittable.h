#ifndef HITTABLE_H
#define HITTABLE_H


// Bundle of data per ray intersection
class hit_record {
public:
    point3 p;
    vec3 normal;
    double t;
    bool front_face;

    // given intersection ray and surface normal, flip the normal if it is facing along the ray (exit points)
    // normal is assumed to be a unit vector
    void set_face_normal(const ray& r, const vec3& outward_normal) {
        // if any axis is opposite, product will be negative
        front_face = (dot(r.direction(), outward_normal) < 0);
        // flip normal if product is positive (ray & normal facing same direction): normal always facing opposite ray (both entry & exit points)
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    // destructor
    virtual ~hittable() = default;

    // calculates ray intersections within valid t values
    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif //HITTABLE_H