#ifndef WORLD_H_
#define WORLD_H_

#include <cstdio>
#include <cstring>
#include <cstdint>
#include <glm/glm.hpp>

#include "transform.h"
#include "collision_detection.h"
#include "collision_manifold.h"

#define WORLD_INSTANCE_COUNT 100
#define WORLD_COLLISION_COUNT WORLD_INSTANCE_COUNT * WORLD_INSTANCE_COUNT

namespace Floorboard {

    struct sWorld {
        bool                  enabled          [WORLD_INSTANCE_COUNT] = {};
        sTransform            transforms       [WORLD_INSTANCE_COUNT] = {};
        eCollisionShapes      collider_shape   [WORLD_INSTANCE_COUNT] = {};

        float                 friction         [WORLD_INSTANCE_COUNT] = {};
        float                 mass             [WORLD_INSTANCE_COUNT] = {};
        float                 inv_mass         [WORLD_INSTANCE_COUNT] = {};

        float                 torque           [WORLD_INSTANCE_COUNT] = {};
        glm::vec2             force            [WORLD_INSTANCE_COUNT] = {};

        glm::vec2             linear_velocity  [WORLD_INSTANCE_COUNT] = {};
        glm::vec2             angular_velocity [WORLD_INSTANCE_COUNT] = {};


        sCollisionManifold    manifolds        [WORLD_COLLISION_COUNT] = {};
        uint16_t              manifold_count                           = 0;


        void init();
        void update(const double elapsed_time);
    };
}


#endif // WORLD_H_
