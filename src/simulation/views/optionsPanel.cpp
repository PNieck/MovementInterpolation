#include <simulation/views/optionsPanel.hpp>

#include <imgui.h>

#include "simulation/controllers/mainController.hpp"


OptionsPanel::OptionsPanel(MainController &controller):
    controller(controller)
{
}


void OptionsPanel::Render() const {
    ImGui::Begin(WindowName());

    const bool simRuns = controller.SimulationIsRunning();

    ImGui::PushItemWidth(-FLT_MIN);

    RenderStartStopButton(simRuns);
    RenderStartFrameOptions(simRuns);
    RenderEndFrameOptions(simRuns);
    RenderInterpolationOptions(simRuns);

    ImGui::PopItemWidth();

    ImGui::End();
}


void OptionsPanel::RenderStartStopButton(const bool simRuns) const {
    ImGui::BeginDisabled(simRuns);

    ImGui::SeparatorText("Simulation");

    if (ImGui::Button("Start")) {
        controller.StartSimulation();
    }
    ImGui::EndDisabled();

    ImGui::SameLine();

    ImGui::BeginDisabled(!simRuns);
    if (ImGui::Button("Stop")) {
        controller.StopSimulation();
    }
    ImGui::EndDisabled();

    ImGui::BeginDisabled(simRuns);
    if (ImGui::Button("Reset")) {
        controller.Reset();
    }
    ImGui::EndDisabled();
}


void OptionsPanel::RenderStartFrameOptions(const bool simRuns) const {
    ImGui::SeparatorText("Start frame");

    const glm::vec3& startPos = controller.GetStartingPosition();
    float coordinates[4] = { startPos.x, startPos.y, startPos.z };

    ImGui::BeginDisabled(simRuns);

    ImGui::Text("Position");
    if (ImGui::DragFloat3("##StartPosition", coordinates, 0.01f)) {
        controller.SetStartingPosition(
            glm::vec3(coordinates[0], coordinates[1], coordinates[2])
        );
    }

    const glm::vec3& eulerAngles = controller.GetStartingOrientationEulerAngles();
    coordinates[0] = eulerAngles.x;
    coordinates[1] = eulerAngles.y;
    coordinates[2] = eulerAngles.z;

    ImGui::Text("Euler angles (XYZ)");
    if (ImGui::DragFloat3("##StartEulerAngles", coordinates, 0.01f)) {
        controller.SetStartingOrientation(
            glm::vec3(coordinates[0], coordinates[1], coordinates[2])
        );
    }

    glm::quat quaternion = controller.GetStartingOrientationQuaternion();
    coordinates[0] = quaternion.w;
    coordinates[1] = quaternion.x;
    coordinates[2] = quaternion.y;
    coordinates[3] = quaternion.z;

    ImGui::Text("Quaternion (WXYZ");
    if (ImGui::DragFloat4("##StartQuaternion", coordinates, 0.01f)) {
        quaternion = { coordinates[0], coordinates[1], coordinates[2], coordinates[3] };
        quaternion = normalize(quaternion);

        controller.SetStartingOrientation(quaternion);
    }

    ImGui::EndDisabled();
}


void OptionsPanel::RenderEndFrameOptions(const bool simRuns) const {
    ImGui::SeparatorText("End frame");

    const glm::vec3& startPos = controller.GetEndingPosition();
    float coordinates[4] = { startPos.x, startPos.y, startPos.z };

    ImGui::BeginDisabled(simRuns);

    ImGui::Text("Position");
    if (ImGui::DragFloat3("##EndPosition", coordinates, 0.01f)) {
        controller.SetEndingPosition(
            glm::vec3(coordinates[0], coordinates[1], coordinates[2])
        );
    }

    const glm::vec3& eulerAngles = controller.GetEndingOrientationEulerAngles();
    coordinates[0] = eulerAngles.x;
    coordinates[1] = eulerAngles.y;
    coordinates[2] = eulerAngles.z;

    ImGui::Text("Euler angles (XYZ)");
    if (ImGui::DragFloat3("##EndEulerAngles", coordinates, 0.01f)) {
        controller.SetEndingOrientation(
            glm::vec3(coordinates[0], coordinates[1], coordinates[2])
        );
    }

    glm::quat quaternion = controller.GetEndingOrientationQuaternion();
    coordinates[0] = quaternion.w;
    coordinates[1] = quaternion.x;
    coordinates[2] = quaternion.y;
    coordinates[3] = quaternion.z;

    ImGui::Text("Quaternion (WXYZ)");
    if (ImGui::DragFloat4("##EndQuaternion", coordinates, 0.01f)) {
        quaternion = { coordinates[0], coordinates[1], coordinates[2], coordinates[3] };
        quaternion = normalize(quaternion);

        controller.SetEndingOrientation(quaternion);
    }

    ImGui::EndDisabled();
}


void OptionsPanel::RenderInterpolationOptions(const bool simRuns) const {
    ImGui::SeparatorText("Interpolation options");

    ImGui::BeginDisabled(simRuns);

    float interpolationTime = controller.GetInterpolationTIme().count();

    ImGui::Text("Interpolation time (s)");
    if (ImGui::DragFloat("##InterpolationTime", &interpolationTime, 0.01f)) {
        controller.SetInterpolationTime(interpolationTime);
    }

    int intermediateCaptures = controller.GetIntermediateFramesToCapture();
    ImGui::Text("Show intermediate frames");
    if (ImGui::DragInt("##IntermediateFrames", &intermediateCaptures)) {
        intermediateCaptures = std::max(0, intermediateCaptures);
        controller.SetNumberOfIntermediateFramesToCapture(intermediateCaptures);
    }

    ImGui::Text("Quaternion interpolation type");

    ImGui::RadioButton("Linear", reinterpret_cast<int *>(&controller.quaternionInterpolationType), 0);
    ImGui::SameLine();
    ImGui::RadioButton("Spherical", reinterpret_cast<int *>(&controller.quaternionInterpolationType), 1);

    ImGui::EndDisabled();
}
