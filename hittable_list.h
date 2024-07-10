#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <vector>

// list of hittable objects of any kind
class hittable_list : public hittable {
public:
    // shared pointers: pointers that keep track of reference count (assignment increases, leaving scope decreases): group of objects shares it
    std::vector<shared_ptr<hittable>> objects;

    // constructors
    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(shared_ptr<hittable> object) {
        objects.push_back(object);
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        // hitting all objects to find which ones are closest to camera and therefore visible
        for (const auto& object : objects) {
            // calling whatever hit function this particular hittable object has
            if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
                hit_anything = true;
                // bump intersection closer to camera from end of valid t range
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};

#endif //HITTABLE_LIST_H