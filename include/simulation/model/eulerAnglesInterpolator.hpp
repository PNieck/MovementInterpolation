#pragma once

#include <glm/vec3.hpp>

#include <algorithm>


class EulerAnglesInterpolator {
public:
    EulerAnglesInterpolator():
        startAngles(0.f),
        endAngles(0.f) {}

    void SetStartAngles(const glm::vec3& angles)
        { startAngles = angles; }

    [[nodiscard]]
    const glm::vec3& GetStartAngles() const
        { return startAngles; }

    void SetEndAngles(const glm::vec3& angles)
        { endAngles = angles; }

    [[nodiscard]]
    const glm::vec3& GetEndAngles() const
        { return endAngles; }

    [[nodiscard]]
    glm::vec3 Interpolate(float t) const;

private:
    glm::vec3 startAngles;
    glm::vec3 endAngles;

    [[nodiscard]]
    glm::vec3 WrapAngle(const glm::vec3& angles) const;

    [[nodiscard]]
    float WrapSingleAngle(float angle) const;
};
