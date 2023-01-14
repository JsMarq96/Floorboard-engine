#ifndef COLLISION_MANIFOLD_H_
#define COLLISION_MANIFOLD_H_

#include <cstdint>
#include <glm/glm.hpp>

namespace Floorboard {

#define CONTACT_POINT_COUNT 6

    struct sCollisionManifold {
        uint16_t   obj1_id = 0;
        uint16_t   obj2_id = 0;

        glm::vec2   normal;

        uint8_t     contact_points_count = 0;
        glm::vec2   contact_points[CONTACT_POINT_COUNT];
        float       contanct_depth[CONTACT_POINT_COUNT];
    };

};

#endif // COLLISION_MANIFOLD_H_
