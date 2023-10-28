#include "ImGui3DAppTest.h"

ImGui3DAppTest::ImGui3DAppTest(const WindowSettings& window_settings)
    :
    ImGui3DApplication(window_settings)
{
}

void ImGui3DAppTest::onUpdate(const float& dt)
{
}

void ImGui3DAppTest::onImGuiUpdate()
{
    ImGui::Begin("TEST");


    ImGui::End();
}
