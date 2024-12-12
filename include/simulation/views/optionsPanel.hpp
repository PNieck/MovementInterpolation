#pragma once


class MainController;


class OptionsPanel {
public:
    explicit OptionsPanel(MainController& controller);

    void Render() const;

    static const char* WindowName()
        { return "Options"; }

private:
    MainController& controller;

    void RenderStartStopButton(bool simRuns) const;
    void RenderStartFrameOptions(bool simRuns) const;
    void RenderEndFrameOptions(bool simRuns) const;
    void RenderInterpolationOptions(bool simRuns) const;
};
