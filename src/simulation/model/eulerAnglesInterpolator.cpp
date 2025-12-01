#include <simulation/model/eulerAnglesInterpolator.hpp>

#include <numbers>


glm::vec3 EulerAnglesInterpolator::Interpolate(float t) const
{
    t = std::clamp(t, 0.0f, 1.0f);

    const auto start = WrapAngle(startAngles);
    const auto end = WrapAngle(endAngles);

    auto diff = end - start;
    diff = WrapAngle(diff);

    const auto result = start + diff * t;

    return WrapAngle(result);
}


glm::vec3 EulerAnglesInterpolator::WrapAngle(const glm::vec3 &angles) const
{
    return {
        WrapSingleAngle(angles.x),
        WrapSingleAngle(angles.y),
        WrapSingleAngle(angles.z)
    };
}


float EulerAnglesInterpolator::WrapSingleAngle(float angle) const
{
    constexpr float pi = std::numbers::pi_v<float>;

    while (angle <= -pi)
        angle += 2 * pi;

    while (angle > pi)
        angle -= 2 * pi;

    return angle;
}
