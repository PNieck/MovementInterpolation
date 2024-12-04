#pragma once

class MainController;


class OptionsPanel {
public:
    explicit OptionsPanel(MainController& controller);

    void Render();

private:
    MainController& controller;

    void RenderStartStopButton(bool simRuns);
    void RenderProperties(bool simRuns);
};
