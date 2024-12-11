#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>


inline glm::mat4 EulerToMatrix(const glm::vec3& eulerAngles) {
    return glm::eulerAngleZ(eulerAngles.z) * glm::eulerAngleY(eulerAngles.y) * glm::eulerAngleX(eulerAngles.x);
}


struct Frame {
    Frame(const glm::vec3& pos, const glm::vec3& euler):
        position(pos), orientation(EulerToMatrix(euler)) {}

    Frame(const glm::vec3& pos, const glm::quat& quat):
        position(pos), orientation(mat4_cast(quat)) {}

    void SetOrientation(const glm::vec3& euler)
        { orientation = EulerToMatrix(euler); }

    void SetOrientation(const glm::quat& quat)
        { orientation = mat4_cast(quat); }

    glm::vec3 position;
    glm::mat4 orientation;
};


inline bool operator==(const Frame& lhs, const Frame& rhs) {
    return lhs.position == rhs.position && lhs.orientation == rhs.orientation;
}
