#include "simulation/views/visualization.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "imgui.h"


Visualization::Visualization(const int xResolution, const int yResolution):
    camera({
        .target = glm::vec3(0.f),
        .viewportWidth = xResolution,
        .viewportHeight = yResolution,
        .fov = std::numbers::pi_v<float> / 4.f,
        .nearPlane = 0.1f,
        .farPlane = 100.0f,
    })
{
}


void Visualization::Update(const glm::quat& q)
{
}


void Visualization::Render() const
{
    glClear(GL_COLOR_BUFFER_BIT);

    const auto view = camera.ViewMatrix();
    const auto projection = camera.ProjectionMatrix();

    const auto cameraMtx = projection * view;

    grid.Render(view, projection);
}


void Visualization::ResizeWindow(const int width, const int height)
{
    glViewport(0, 0, width, height);
    camera.SetViewportSize(width, height);
}


void Visualization::RotateCamera(const float x, const float y)
{
    const auto oldPos = camera.GetPosition();

    auto rotation = glm::mat4(
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f
    );

    rotation = glm::rotate(rotation, x, glm::vec3(0.f, 1.f, 0.f));

    const auto axis = glm::cross(oldPos, glm::vec3(0.f, 1.f, 0.f));
    rotation = glm::rotate(rotation, y, axis);

    const auto newPos = rotation * glm::vec4(oldPos, 1.f);
    camera.SetPosition(glm::vec3(newPos.x, newPos.y, newPos.z));
}
