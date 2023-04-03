#pragma once

#include "Application.h"


class ImGuiApplication : public Application
{
public:

    ImGuiApplication(const WindowSettings& window_settings);

    void run();

protected:

    void loop();

    virtual void onUpdate(const float& dt) = 0;

    virtual void onImGuiUpdate() = 0;

private:

    void imGuiInit();
    void imGuiNewFrame();
    void imGuiRender();
    void imGuiShutdown();

};

