#pragma once
#include "Application.h"
#include "dll.h"
#include "Controller3D.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>


class ImGui3DApplication : public Application
{
public:

    L4_API ImGui3DApplication(const WindowSettings& window_settings);

    L4_API void run() override;

protected:

    L4_API void loop() override;

    L4_API virtual void onUpdate(const float& dt) = 0;

    L4_API virtual void onImGuiUpdate() = 0;

private:

    void imGuiInit();
    void imGuiNewFrame();
    void imGuiRender();
    void imGuiShutdown();

private:

    Controller3D* m_controller3D;

};

