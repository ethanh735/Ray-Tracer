#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"

class hit_record;

// abstract class that encapsulates unique behaviors
class material {
  public:
    virtual ~material() = default;

    // whether incident ray is reflected or absorbed by material
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
        return false;
    }
};

// Labert diffuse material: always scattering and attenuating light (reflected rays)
// attenuation: gradual loss of (light) intensity through a medium
// albedo: fraction of how much light is diffusely reflected
class lambertian : public material {
  public:
    lambertian(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();

        // can't have randomly generated ray be exactly the opposite of normal: scatter_direction would be 0 / NaN
        if (scatter_direction.near_zero()) {
            scatter_direction = rec.normal;
        }

        scattered = ray(rec.p, scatter_direction, r_in.time());
        attenuation = albedo;       // how light or dark material is: essentially material color
        return true;
    }

  private:
    color albedo;
};

class metal : public material {
  public:
    metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        vec3 reflected = reflect(r_in.direction(), rec.normal);             // instead of random reflection angle, exacting reflection
        reflected = unit_vector(reflected) + (fuzz * random_unit_vector());    // offset endpoint of reflection by fuzz amount, accounting for (normalizing) reflection distance

        scattered = ray(rec.p, reflected, r_in.time());
        attenuation = albedo;                                                     // how light or dark material is: essentially material color
        return (dot(scattered.direction(), rec.normal) > 0);                // returns true if reflection is away from object (absorbs scattering below surface)
    }

  private:
    color albedo;
    double fuzz;
};

class dielectric : public material {
public:
    dielectric(double refraction_index) : refraction_index(refraction_index) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        attenuation = color(1.0, 1.0, 1.0);                                 // glass doesn't absorb rays
        double ri = rec.front_face ? (1.0/refraction_index) : refraction_index;         // refraction index is either itself, or ratio of this material and material its enclosed in

        vec3 unit_direction = unit_vector(r_in.direction());

        double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);          // -R * n
        double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

        vec3 direction;

        if (ri * sin_theta > 1.0 || reflectance(cos_theta, ri) > random_double()) {
            // Must Reflect: total internal reflection, n1/n2 * sin(theta_1) too great for refracted angle to exit surface
            direction = reflect(unit_direction, rec.normal);
        }
        else {
            // Can Refract
            direction = refract(unit_direction, rec.normal, ri);    // dot product simplified by input ray being unit vector
        }

        scattered = ray(rec.p, direction, r_in.time());
        return true;
    }

private:
    // Refractive index in vacuum or air, or the ratio of the material's refractive index over the refractive index of the enclosing media
    double refraction_index;

    // Use Schlick's approximation for reflectance
    static double reflectance(double cosine, double refraction_index) {
        auto r0 = (1 - refraction_index) / (1 + refraction_index);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1 - cosine),5);
    }
};

#endif