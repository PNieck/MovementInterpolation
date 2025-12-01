#include <simulation/model/quaternionInterpolator.hpp>


glm::quat QuaternionInterpolator::Interpolate(const float t, const Types type) const
{
    switch (type) {
        case Linear: return InterpolateLinearly(t);
        case Spherical: return InterpolateSpherically(t);

        default:
            throw std::runtime_error("Unknown interpolation type");
    }
}


glm::quat QuaternionInterpolator::InterpolateLinearly(float t) const {
    t = std::clamp(t, 0.0f, 1.0f);

    glm::quat adjustedEnd = endQuaternion;
    if (glm::dot(startQuaternion, endQuaternion) < 0.f)
        adjustedEnd = -adjustedEnd;

    const glm::quat rotation = startQuaternion + (adjustedEnd - startQuaternion) * t;
    return glm::normalize(rotation);
}


glm::quat QuaternionInterpolator::InterpolateSpherically(float t) const
{
    t = std::clamp(t, 0.0f, 1.0f);

    glm::quat adjustedEnd = endQuaternion;
    float dot = glm::dot(startQuaternion, adjustedEnd);
    if (dot < 0.f) {
        adjustedEnd = -adjustedEnd;
        dot = -dot;
    }

    const float omega = static_cast<float>(acos(dot));
    const float invSinOmega = 1.0f / static_cast<float>(sin(omega));

    const float v1 = static_cast<float>(sin((1.0f - t) * omega)) * invSinOmega;
    const float v2 = static_cast<float>(sin(t * omega)) * invSinOmega;

    return glm::normalize(startQuaternion * v1 + adjustedEnd * v2);
}
