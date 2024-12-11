#pragma once

#include <glm/vec3.hpp>

#include <algorithm>


class PositionInterpolator {
public:
    PositionInterpolator():
        startPosition(0.f),
        endPosition(0.f) {}

    void SetStartPosition(const glm::vec3& position)
        { startPosition = position; }

    [[nodiscard]]
    const glm::vec3& GetStartPosition() const
        { return startPosition; }

    void SetEndPosition(const glm::vec3& position)
        { endPosition = position; }

    [[nodiscard]]
    const glm::vec3& GetEndPosition() const
        { return endPosition; }

    [[nodiscard]]
    glm::vec3 Interpolate(float t) const {
        t = std::clamp(t, 0.0f, 1.0f);
        return startPosition + (endPosition - startPosition) * t;
    }

private:
    glm::vec3 startPosition;
    glm::vec3 endPosition;
};
