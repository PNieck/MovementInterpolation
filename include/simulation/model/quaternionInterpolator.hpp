#pragma once

#include <algorithm>
#include <filesystem>

#include "glm/glm.hpp"
#include "glm/ext/quaternion_common.hpp"

class QuaternionInterpolator {
public:
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
    glm::quat Interpolate(float t) const {
        t = std::clamp(t, 0.0f, 1.0f);
        return lerp(startQuaternion, endQuaternion, t);
    }

private:
    glm::quat startQuaternion;
    glm::quat endQuaternion;
};
