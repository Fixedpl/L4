#include "Test.h"

#include <imgui/imgui.h>


Test::Test()
    :
    m_window(nullptr)
{
}

Test::Test(Window* window)
    :
    m_window(window)
{
}

void Test::_onImGuiUpdate()
{
    ImGui::Begin("Test");

    onImGuiUpdate();

    if (ImGui::Button("<-")) {
        m_on_test_end_callback();
    }

    ImGui::End();
}

