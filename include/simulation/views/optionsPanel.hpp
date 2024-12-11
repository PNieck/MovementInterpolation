#pragma once

class MainController;


class OptionsPanel {
public:
    explicit OptionsPanel(MainController& controller);

    void Render();

    static const char* WindowName()
        { return "Options"; }

private:
    MainController& controller;

    void RenderStartStopButton(bool simRuns);
    void RenderStartFrameOptions(bool simRuns) const;
    void RenderEndFrameOptions(bool simRuns) const;
};
