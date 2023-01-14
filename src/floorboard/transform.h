#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

struct sTransform {
    glm::vec2   position = {0.0f, 0.0f};
    glm::vec2   scale    = {1.0f, 1.0f};
    float       rotation = 0.0f;

    inline void set_identity() {
        position = {0.0f, 0.0f};
        scale    = {1.0f, 1.0f};
        rotation = 0.0f;
    }

    inline glm::mat3 get_model() const {
        return glm::translate(glm::mat3{1.0f},
                              position) * glm::rotate(glm::mat3{1.0f},
                                                      rotation) * glm::scale( glm::mat3{1.0f},
                                                                              scale );
    }
};

#endif // TRANSFORM_H_
