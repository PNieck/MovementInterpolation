#pragma once

#include "mouseState.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../views/dockingSpace.hpp"
#include "../views/optionsPanel.hpp"
#include "../views/visualization.hpp"

#include "../model/positionInterpolator.hpp"
#include "../model/quaternionInterpolator.hpp"
#include "../model/eulerAnglesInterpolator.hpp"


class MainController {
public:
    explicit MainController(GLFWwindow* window);
    ~MainController();

    void Update();

    void StartSimulation()
        {  }

    void StopSimulation()
        {  }

    void UpdateSimulation()
        {  }

    [[nodiscard]]
    bool SimulationIsRunning() const
        { return false; }

    void Render();

    void MouseClicked(const MouseButton button)
        { mouseState.ButtonClicked(button); }

    void MouseReleased(const MouseButton button)
        { mouseState.ButtonReleased(button); }

    void MouseMoved(int x, int y);
    void ScrollMoved(int offset);

    static const char* QuaternionVisualizationWindowName()
        { return "Quaternion interpolation"; }

    static const char* EulerVisualizationWindowName()
        { return "Euler angles interpolation"; }

    void SetStartingPosition(const glm::vec3& position)
        { positionInterpolator.SetStartPosition(position); }

    void SetEndingPosition(const glm::vec3& position)
        { positionInterpolator.SetEndPosition(position); }

    void SetStartingOrientation(const glm::quat& orientation);
    void SetStartingOrientation(const glm::vec3& orientation);

    void SetEndingOrientation(const glm::quat& orientation);
    void SetEndingOrientation(const glm::vec3& orientation);

    [[nodiscard]]
    const glm::vec3& GetEndingPosition() const
        { return positionInterpolator.GetEndPosition(); }

    [[nodiscard]]
    const glm::vec3& GetStartingPosition() const
        { return positionInterpolator.GetStartPosition(); }

    [[nodiscard]]
    const glm::quat& GetStartingOrientationQuaternion() const
        { return quaternionInterpolator.GetStartQuaternion(); }

    [[nodiscard]]
    const glm::vec3& GetStartingOrientationEulerAngles() const
        { return eulerAnglesInterpolator.GetStartAngles(); }

    [[nodiscard]]
    const glm::quat& GetEndingOrientationQuaternion() const
        { return quaternionInterpolator.GetEndQuaternion(); }

    [[nodiscard]]
    const glm::vec3& GetEndingOrientationEulerAngles() const
        { return eulerAnglesInterpolator.GetEndAngles(); }

private:
    MouseState mouseState;

    DockingSpace dockingSpace;
    OptionsPanel optionsPanel;
    Visualization visualizationQuat;
    Visualization visualizationEuler;

    PositionInterpolator positionInterpolator;
    QuaternionInterpolator quaternionInterpolator;
    EulerAnglesInterpolator eulerAnglesInterpolator;

    std::vector<glm::vec3> positions;
    std::vector<glm::mat4> rotations;

    [[nodiscard]]
    bool WantToCaptureMouse() const;
};
