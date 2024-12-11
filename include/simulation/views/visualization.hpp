#pragma once

#include "visualization/camera.hpp"
#include "visualization/grid.hpp"
#include "visualization/shaders/stdShader.hpp"
#include "visualization/shaders/phongShader.hpp"
#include "visualization/framebuffer.hpp"
#include "visualization/frame.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "visualization/renderObject.hpp"


class Visualization {
public:
    Visualization(const char* windowName, int xResolution, int yResolution);

    void Render(const Frame& start, const Frame& end, const Frame& actual);

    void RotateCamera(float x, float y);

    [[nodiscard]]
    glm::vec3 GetCameraPosition() const
        { return camera.GetPosition(); }

    void SetCameraPosition(const glm::vec3& position)
        { camera.SetPosition(position); }

    [[nodiscard]]
    bool IsMouseOverWindow() const
        { return mouseIsOver; }

private:
    static constexpr auto red = glm::vec4(1.0f, 0.0f, 0.0f, 1.f);
    static constexpr auto green = glm::vec4(0.0f, 1.0f, 0.0f, 1.f);
    static constexpr auto blue = glm::vec4(0.0f, 0.0f, 1.0f, 1.f);

    const char* windowName;
    bool mouseIsOver = false;

    Camera camera;
    Grid grid;

    RenderObject arrow;

    Framebuffer framebuffer;

    StdShader shader;
    PhongShader phongShader;

    void RenderFrame(const Frame& frame, const glm::mat4& view, const glm::mat4& projection);
};
