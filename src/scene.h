#ifndef SCENE_H
#define SCENE_H

/*  Stores shapes in a 3d scene and provides (soon-to-be efficient) 
    accessors to various objects
*/
#include <vector>
#include <memory>
#include <Eigen/Core>
#include "shape.h"
#include "light.h"
#include "camera.h"
#include "materials/solid_material.h"

using Eigen::Vector3f, Eigen::Vector3i;

class Scene {
    protected:
        // animation variables
        unsigned int scene_time_steps;
        float dt;
        float curr_t;

    public:
        virtual ~Scene() {}

        // Camera to shoot rays from
        Camera cam;

        // TODO: implement spatial binning
        std::vector<std::shared_ptr<Shape>> scene_shapes;

        // TODO: declare superclass for different light and objectify them
        std::vector<std::shared_ptr<PointLight>> lights;
        
        const float bounds = 6.0;

        std::shared_ptr<SolidMaterial> background = std::make_shared<SolidMaterial>(222,222,222);

        Vector3f ambient_light = Vector3f(100, 100, 100);
        
        std::shared_ptr<Shape> nearest_shape(Vector3f p) {
            std::shared_ptr<Shape> ret = nullptr;
            float min_distance = std::numeric_limits<float>::infinity();

            for (auto& s : scene_shapes) {
                float d = s->wdist(p);
                if (d < min_distance) {
                    ret = s;
                    min_distance = d;
                }
            }

            return ret;
        }

        void add_shape(std::shared_ptr<Shape> shape) {
            this->scene_shapes.push_back(shape);
        }

        void add_light(std::shared_ptr<PointLight> plight) {
            this->lights.push_back(plight);
        }

        // continue one step in the animation
        virtual void step_time() = 0;

        int num_steps() {
            return scene_time_steps;
        }

};

#endif