#pragma once

#include "mouseState.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../views/dockingSpace.hpp"
#include "../views/optionsPanel.hpp"
#include "../views/visualization.hpp"

#include "../model/model.hpp"


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
        { return true; }

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

private:
    MouseState mouseState;

    DockingSpace dockingSpace;
    OptionsPanel optionsPanel;
    Visualization visualizationQuat;
    Visualization visualizationEuler;

    Model model;

    [[nodiscard]]
    bool WantToCaptureMouse() const;
};
