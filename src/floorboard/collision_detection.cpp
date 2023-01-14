#include "collision_detection.h"
#include <glm/ext/quaternion_geometric.hpp>

// TODO: Just two (the intersection) points are enought for the AABB contancts..?
inline bool Floorboard::ColDet::collision_AABB_AABB(const sTransform &transform1,
                                                    const sTransform &transform2,
                                                    sCollisionManifold *manifold) {
    const glm::vec2 center_dist = glm::abs(transform1.position - transform2.position);
    const glm::vec2 half_size_1 = transform1.scale / 2.0f, half_size_2 = transform2.scale / 2.0f;
    const glm::vec2 half_size_diff = half_size_1 - half_size_2;

    bool x = center_dist.x <= half_size_diff.x;
    bool y = center_dist.y <= half_size_diff.y;

    if (!(x && y)) {
        return false;
    }

    manifold->normal = glm::normalize(transform1.position - transform2.position);

    const glm::vec2 min_1 = transform1.position - half_size_1, min_2 = transform2.position - half_size_2;
    const glm::vec2 max_1 = transform1.position + half_size_1, max_2 = transform2.position + half_size_2;

    manifold->contact_points[0] = glm::vec2{ glm::min(min_1.x, min_2.x), glm::min(max_1.y, max_2.y) };
    manifold->contact_points[0] = glm::vec2{ glm::max(max_1.x, max_2.x), glm::max(min_1.y, min_2.y) };

    manifold->contact_points_count = 2;

    return true;

}

inline bool Floorboard::ColDet::collision_OBB_AABB(const sTransform &transform1,
                                                   const sTransform &transform2,
                                                   sCollisionManifold *manifold) {
    return false;
}

inline bool Floorboard::ColDet::collision_OBB_OBB(const sTransform &transform1,
                                                  const sTransform &transform2,
                                                  sCollisionManifold *manifold) {
    return false;
}

inline bool Floorboard::ColDet::collision_sphere_AABB(const sTransform &transform1,
                                                      const sTransform &transform2,
                                                      sCollisionManifold *manifold) {
    return false;
}

inline bool Floorboard::ColDet::collision_sphere_sphere(const sTransform &transform1,
                                                        const sTransform &transform2,
                                                        sCollisionManifold *manifold) {
    return false;
}

// TODO complete cases
#define COMPARE(obj1, obj2) obj1_shape == obj1 && obj2_shape == obj2
inline bool Floorboard::ColDet::detect_collision(const sTransform &obj1_transform,
                                                 const eCollisionShapes obj1_shape,
                                                 const sTransform &obj2_transform,
                                                 const eCollisionShapes obj2_shape,
                                                 sCollisionManifold *manifold) {
    bool result = false;

    if (COMPARE(AABB, AABB)) {
        result = collision_AABB_AABB(obj1_transform,
                                     obj2_transform,
                                     manifold);
    } else if (COMPARE(SPHERE, SPHERE)) {
        result = collision_sphere_sphere(obj1_transform,
                                         obj2_transform,
                                         manifold);
    } else if (COMPARE(OBB, OBB)) {
        result = collision_OBB_OBB(obj1_transform,
                                   obj2_transform,
                                   manifold);
    } else if (COMPARE(OBB, AABB)) {
        result = collision_OBB_AABB(obj1_transform,
                                    obj2_transform,
                                    manifold);
    } else if (COMPARE(AABB, OBB)) {
        result = collision_OBB_AABB(obj2_transform,
                                    obj1_transform,
                                    manifold);
        manifold->normal = manifold->normal * -1.0f;
    } else if (COMPARE(SPHERE, AABB)) {
        result = collision_sphere_AABB(obj1_transform,
                                       obj2_transform,
                                       manifold);
    } else if(COMPARE(AABB, SPHERE)) {
        result = collision_sphere_AABB(obj2_transform,
                                       obj1_transform,
                                       manifold);
        manifold->normal = manifold->normal * -1.0f;
    }

    return result;
}
