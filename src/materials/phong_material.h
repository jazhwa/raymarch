#ifndef PHONG_MATERIAL_H
#define PHONG_MATERIAL_H

/* Basic Phong shading
*/

#include <Eigen/Core>
#include "material.h"

using Eigen::Vector3i, Eigen::Vector3f;

class PhongMaterial: public Material {
    private:
        float Ka = 1.0; // ambient reflect coeff
        float Kd = 0.8; // diffuse reflect coeff
        float Ks = 0.2; // specular reflect coeff
        float alpha = 12.0; // shininess
        Vector3f albedo;

    public:
        PhongMaterial() {}

        PhongMaterial(Vector3f albedo) {
            this->albedo = albedo;
        }

        PhongMaterial(Vector3f albedo, float Ka, float Kd, float Ks, float alpha) {
            this->albedo = albedo;
            this->Ka = Ka;
            this->Kd = Kd;
            this->Ks = Ks;
            this->alpha = alpha;
        }

        Vector3i shade(Vector3f location, Vector3f normal, const Scene& scene) {
            Vector3f N = normal.normalized();
            Vector3f L, R, V, intensity;
            Vector3f rgb(0.0,0.0,0.0);
            float lambertian, specAngle;
            
            // compute ambient
            rgb += Ka * scene.ambient_light.cwiseProduct(this->albedo);

            for (auto& light: scene.lights) {

                intensity = light->intensity(location);
                L = (light->position - location).normalized();

                // compute diffuse
                V = (scene.cam.location - location).normalized();
                lambertian = fmax(L.dot(N), 0.0);
                rgb += Kd*lambertian*(intensity.cwiseProduct(this->albedo));

                // compute specular
                R = 2.0 * (L.dot(N))*N - L; // reflect L on plane defined by N
                specAngle = fmax(R.dot(V), 0.0);
                rgb += Ks*(std::pow(specAngle, alpha))*intensity;
            }

            // TODO: figure a nicer way to clamp these values
            return Vector3i(fmin(254.0, rgb(0)), fmin(254.0,rgb(1)), fmin(254.0, rgb(2)));
        }
};

#endif