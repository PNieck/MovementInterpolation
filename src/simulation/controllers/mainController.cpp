#include <simulation/controllers/mainController.hpp>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


MainController::MainController(GLFWwindow *window):
    optionsPanel(*this),
    visualizationQuat(QuaternionVisualizationWindowName(), 1280, 720),
    visualizationEuler(EulerVisualizationWindowName(), 1280, 720),
    interpolationInterval(1.f)
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
    if (simulationStarted) {
        actualTime = std::chrono::high_resolution_clock::now();
    }
}


void MainController::StartSimulation() {
    startTime = std::chrono::high_resolution_clock::now();

    simulationStarted = true;
}


void MainController::Render()
{
    // Creating new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    dockingSpace.Render();
    optionsPanel.Render();

    std::vector<Frame> frames {
        { GetStartingPosition(), GetStartingOrientationQuaternion() },
        { GetEndingPosition(), GetEndingOrientationQuaternion() }
    };

    const auto actFrames = ActualFrame();

    if (actFrames.has_value())
        frames.push_back(actFrames.value().QuatInter);

    visualizationQuat.Render(frames);

    frames[0].SetOrientation(GetStartingOrientationEulerAngles());
    frames[1].SetOrientation(GetEndingOrientationEulerAngles());

    if (actFrames.has_value())
        frames[2] = actFrames.value().EulerInter;

    visualizationEuler.Render(frames);

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

    const auto newCamPos = camPos * val;
    visualizationQuat.SetCameraPosition(newCamPos);
    visualizationEuler.SetCameraPosition(newCamPos);
}


void MainController::SetStartingOrientation(const glm::quat &orientation) {
    const glm::vec3 eulerAngles = glm::eulerAngles(orientation);

    quaternionInterpolator.SetStartQuaternion(orientation);
    eulerAnglesInterpolator.SetStartAngles(eulerAngles);
}


void MainController::SetStartingOrientation(const glm::vec3 &orientation) {
    const auto quaternion = glm::quat(orientation);

    eulerAnglesInterpolator.SetStartAngles(orientation);
    quaternionInterpolator.SetStartQuaternion(quaternion);
}


void MainController::SetEndingOrientation(const glm::quat &orientation) {
    const glm::vec3 eulerAngles = glm::eulerAngles(orientation);

    quaternionInterpolator.SetEndQuaternion(orientation);
    eulerAnglesInterpolator.SetEndAngles(eulerAngles);
}


void MainController::SetEndingOrientation(const glm::vec3 &orientation) {
    const auto quaternion = glm::quat(orientation);

    eulerAnglesInterpolator.SetEndAngles(orientation);
    quaternionInterpolator.SetEndQuaternion(quaternion);
}


bool MainController::WantToCaptureMouse() const
{
    return !(visualizationEuler.IsMouseOverWindow() || visualizationQuat.IsMouseOverWindow());
}


std::optional<MainController::Frames> MainController::ActualFrame() {
    if (!SimulationIsRunning())
        return std::nullopt;

    const float t = (std::chrono::high_resolution_clock::now() - startTime) / interpolationInterval;
    if (t > 1.f)
        StopSimulation();

    const auto pos = positionInterpolator.Interpolate(t);

    return Frames {
        .QuatInter = Frame(pos, quaternionInterpolator.Interpolate(t)),
        .EulerInter = Frame(pos, eulerAnglesInterpolator.Interpolate(t))
    };
}
