#include <simulation/views/optionsPanel.hpp>

#include <imgui.h>

#include "simulation/controllers/mainController.hpp"


OptionsPanel::OptionsPanel(MainController &controller):
    controller(controller)
{
}


void OptionsPanel::Render()
{
    ImGui::Begin("Options");

    const bool simRuns = controller.SimulationIsRunning();

    RenderStartStopButton(simRuns);
    //RenderProperties(simRuns);

    ImGui::End();
}


void OptionsPanel::RenderStartStopButton(const bool simRuns)
{
    ImGui::BeginDisabled(simRuns);
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
    if (ImGui::Button("Update")) {
        controller.UpdateSimulation();
    }

    if (ImGui::Button("Reset")) {
        //controller.SetProperties(properties);
    }
    ImGui::EndDisabled();
}
