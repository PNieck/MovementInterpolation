#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>


struct Frame {
    glm::vec3 position;
    glm::mat4 orientation;
};


inline bool operator==(const Frame& lhs, const Frame& rhs) {
    return lhs.position == rhs.position && lhs.orientation == rhs.orientation;
}
