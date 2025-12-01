#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <algorithm>
#include <filesystem>

#include "glm/glm.hpp"
#include "glm/ext/quaternion_common.hpp"
#include <glm/gtx/quaternion.hpp>

class QuaternionInterpolator {
public:
    enum Types: int {
        Linear = 0,
        Spherical = 1
    };

    QuaternionInterpolator():
        startQuaternion(1.f, 0.f, 0.f, 0.f),
        endQuaternion(1.f, 0.f, 0.f, 0.f) {}

    void SetStartQuaternion(const glm::quat& quaternion)
        { startQuaternion = quaternion; }

    [[nodiscard]]
    const glm::quat& GetStartQuaternion() const
        { return startQuaternion; }

    void SetEndQuaternion(const glm::quat& quaternion)
        { endQuaternion = quaternion; }

    [[nodiscard]]
    const glm::quat& GetEndQuaternion() const
        { return endQuaternion; }

    [[nodiscard]]
    glm::quat Interpolate(float t, Types type) const;

    [[nodiscard]]
    glm::quat InterpolateLinearly(float t) const;

    [[nodiscard]]
    glm::quat InterpolateSpherically(float t) const;

private:
    glm::quat startQuaternion;
    glm::quat endQuaternion;
};
