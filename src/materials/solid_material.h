#ifndef SOLID_MATERIAL_H
#define SOLID_MATERIAL_H

/* No shading, just a color
*/
#include <Eigen/Core>
#include "material.h"

using Eigen::Vector3i, Eigen::Vector3f;

class SolidMaterial: public Material {
    public:
        Vector3i color;

        SolidMaterial(int r, int g, int b) {
            this->color = Vector3i(r,g,b);
        }

        Vector3i shade(Vector3f location, Vector3f normal, const Scene& scene) {
            (void) location;
            (void) normal;
            (void) scene;
            return this->color;
        }

};

#endif