#include "world.h"
#include "collision_detection.h"
#include "collision_manifold.h"
#include <cstdint>

#define GRAVITY_CONSTANT glm::vec2{0.0f, -10.0f}

void Floorboard::sWorld::init() {
    memset(enabled, false, sizeof(enabled));
    memset(inv_mass, 0.0f, sizeof(inv_mass));
}

void Floorboard::sWorld::update(const double elapsed_time) {

    glm::vec2 elapsed_time_vec = glm::vec2{ elapsed_time, elapsed_time };

    // Search for collisions ============================
    manifold_count = 0;
    sCollisionManifold *manifold_it = manifolds;
    for(uint16_t i = 0; i < WORLD_INSTANCE_COUNT; i++) {
        if (!enabled[i]) {
            continue;
        }
        for(uint16_t j = i+1; j < WORLD_INSTANCE_COUNT; j++) {
            if (!enabled[j]) {
                continue;
            }

            if (ColDet::detect_collision(transforms[i],
                                         collider_shape[i],
                                         transforms[j],
                                         collider_shape[j],
                                         manifold_it)) {
                manifold_it->obj1_id = i;
                manifold_it->obj2_id = j;
                manifold_it++;
                manifold_count++;
            }
        }
    }

    // Integrate forces ==================================
    for(uint16_t i = 0; i < WORLD_INSTANCE_COUNT; i++) {
        if (!enabled[i] || inv_mass[i] == 0.0f) {
            continue;
        }

        linear_velocity[i] += elapsed_time_vec * (GRAVITY_CONSTANT + inv_mass[i] * force[i]);
    }
}
