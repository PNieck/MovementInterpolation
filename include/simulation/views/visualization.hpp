#pragma once

#include "visualization/camera.hpp"
#include "visualization/grid.hpp"
#include "visualization/renderObject.hpp"
#include "visualization/shaders/stdShader.hpp"
#include "visualization/mesh.hpp"
#include "visualization/framebuffer.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>


class Visualization {
public:
    Visualization(const char* windowName, int xResolution, int yResolution);

    void Update(const glm::quat& q);

    void Render();

    void RotateCamera(float x, float y);

    [[nodiscard]]
    glm::vec3 GetCameraPosition() const
        { return camera.GetPosition(); }

    void SetCameraPosition(const glm::vec3& position)
        { camera.SetPosition(position); }

    [[nodiscard]]
    static const char* WindowName()
        { return "Visualization options"; }

    [[nodiscard]]
    bool IsMouseOverWindow() const
        { return mouseIsOver; }

private:
    const char* windowName;
    bool mouseIsOver = false;

    Camera camera;
    Grid grid;

    Framebuffer framebuffer;

    StdShader shader;
};
