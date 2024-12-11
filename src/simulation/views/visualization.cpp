#include "simulation/views/visualization.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <numbers>
#include <ranges>

#include <simulation/views/visualization/meshLoader.hpp>

#include "imgui.h"
#include <glm/gtx/euler_angles.hpp>


Visualization::Visualization(const char* windowName, const int xResolution, const int yResolution):
    windowName(windowName),
    camera({
        .target = glm::vec3(0.f),
        .viewportWidth = xResolution,
        .viewportHeight = yResolution,
        .fov = std::numbers::pi_v<float> / 4.f,
        .nearPlane = 0.5f,
        .farPlane = 100.0f,
    }),
    framebuffer(xResolution, yResolution)
{
    glViewport(0, 0, xResolution, yResolution);

    const auto data = MeshLoader::LoadWithNormals("../../models/arrow.obj");
    arrow.UpdateMesh(std::get<0>(data), std::get<1>(data));
}


void Visualization::Render(const std::vector<Frame>& frames)
{
    glClear(GL_COLOR_BUFFER_BIT);

    const auto view = camera.ViewMatrix();
    const auto projection = camera.ProjectionMatrix();

    ImGui::Begin(windowName);

    mouseIsOver = ImGui::IsWindowHovered();

    framebuffer.Use();

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const auto& frame : frames) {
        RenderFrame(frame, view, projection);
    }

    glEnable(GL_BLEND);
    const auto camParams = camera.GetParameters();
    grid.Render(view, projection, camParams.nearPlane, camParams.farPlane);

    Framebuffer::UseDefault();

    const uint64_t textureID = framebuffer.GetColorTextureId();
    const ImVec2 size = ImGui::GetContentRegionAvail();
    ImGui::Image(textureID, ImVec2{ size.x, size.y }, ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
    ImGui::End();
}


void Visualization::RotateCamera(const float x, const float y)
{
    const auto oldPos = camera.GetPosition();

    auto rotation = glm::rotate(glm::mat4(1.f), x, glm::vec3(0.f, 1.f, 0.f));

    const auto axis = glm::cross(oldPos, glm::vec3(0.f, 1.f, 0.f));
    rotation = glm::rotate(rotation, y, axis);

    const auto newPos = rotation * glm::vec4(oldPos, 1.f);
    camera.SetPosition(glm::vec3(newPos.x, newPos.y, newPos.z));
}


void Visualization::RenderFrame(const Frame& frame, const glm::mat4& view, const glm::mat4& projection) {
    phongShader.Use();
    phongShader.SetCameraPosition(camera.GetPosition());
    phongShader.SetLightPosition(glm::vec3(10.0f, 10.f, 10.f));
    phongShader.SetProjectionMatrix(projection);
    phongShader.SetViewMatrix(view);

    arrow.SetPosition(frame.position);
    arrow.SetRotation(frame.orientation);
    arrow.SetColor(green);
    arrow.Render(phongShader);

    arrow.SetRotation(frame.orientation * glm::eulerAngleX(glm::half_pi<float>()));
    arrow.SetColor(red);
    arrow.Render(phongShader);

    arrow.SetRotation(frame.orientation * glm::eulerAngleZ(glm::half_pi<float>()));
    arrow.SetColor(blue);
    arrow.Render(phongShader);
}
