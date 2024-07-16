#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"

class hit_record;

// abstract class that encapsulates unique behaviors
class material {
  public:
    virtual ~material() = default;

    // whether incident ray is reflected or absorbed by material
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const {
        return false;
    }
};

#endif