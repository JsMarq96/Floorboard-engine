#ifndef COLLISION_DETECTION_H_
#define COLLISION_DETECTION_H_

#include <glm/glm.hpp>

#include "collision_manifold.h"
#include "transform.h"

namespace Floorboard {

    enum eCollisionShapes : uint8_t {
        AABB = 0,
        OBB,
        SPHERE,
        COLLISION_SHAPE_COUNT
    };

    namespace ColDet {

        inline bool detect_collision(const sTransform &obj1_transform,
                                     const eCollisionShapes obj1_shape,
                                     const sTransform &obj2_transform,
                                     const eCollisionShapes obj2_shape,
                                     sCollisionManifold *manifold);

        // ===================
        // DISCRETE COLLISION FUNCTIONS
        // ==================
        inline bool collision_AABB_AABB(const sTransform &transform1,
                                        const sTransform &transform2,
                                        sCollisionManifold *manifold);

        inline bool collision_OBB_AABB(const sTransform &transform1,
                                       const sTransform &transform2,
                                       sCollisionManifold *manifold);

        inline bool collision_OBB_OBB(const sTransform &transform1,
                                      const sTransform &transform2,
                                      sCollisionManifold *manifold);

        inline bool collision_sphere_AABB(const sTransform &transform1,
                                          const sTransform &transform2,
                                          sCollisionManifold *manifold);

        inline bool collision_sphere_sphere(const sTransform &transform1,
                                            const sTransform &transform2,
                                            sCollisionManifold *manifold);
    }
}


#endif // COLLISION_DETECTION_H_
