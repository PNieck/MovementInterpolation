#include <simulation/controllers/mainController.hpp>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


MainController::MainController(GLFWwindow *window):
    optionsPanel(*this),
    visualizationQuat(QuaternionVisualizationWindowName(), 1280, 720),
    visualizationEuler(EulerVisualizationWindowName(), 1280, 720)
{
    const auto glsl_version = "#version 410";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
    ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
#endif
    ImGui_ImplOpenGL3_Init(glsl_version);
}


MainController::~MainController()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}


void MainController::Update()
{
}


void MainController::Render()
{
    // Creating new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    dockingSpace.Render();
    optionsPanel.Render();
    visualizationQuat.Render();
    visualizationEuler.Render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void MainController::MouseMoved(const int x, const int y)
{
    mouseState.Moved(x, y);

    if (WantToCaptureMouse())
        return;

    if (mouseState.IsButtonClicked(MouseButton::Middle)) {
        const auto offset = mouseState.TranslationGet();
        visualizationQuat.RotateCamera(
            offset.x * 0.02f, offset.y * 0.02f
        );

        const auto camPos = visualizationQuat.GetCameraPosition();
        visualizationEuler.SetCameraPosition(camPos);
    }
}


void MainController::ScrollMoved(const int offset)
{
    if (WantToCaptureMouse())
        return;

    float val = offset * 0.7f;

    if (val < 0.0f) {
        val = -1.0f / val;
    }

    const auto camPos = visualizationQuat.GetCameraPosition();

    auto newCamPos = camPos * val;
    visualizationQuat.SetCameraPosition(newCamPos);
    visualizationEuler.SetCameraPosition(newCamPos);
}


bool MainController::WantToCaptureMouse() const
{
    return !(visualizationEuler.IsMouseOverWindow() || visualizationQuat.IsMouseOverWindow());
}
