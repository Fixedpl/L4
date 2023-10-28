#include "TestingEnvironment.h"


#include <imgui/imgui.h>
#include <glm/gtx/string_cast.hpp>



TestingEnvironment::TestingEnvironment(const WindowSettings& window_settings)
    :
    ImGuiApplication(window_settings),
    m_current_test(&m_empty_test)
{
}

void TestingEnvironment::loadTest(const std::string& name)
{
    m_current_test = m_tests[name]();
}

void TestingEnvironment::onUpdate(const float& frame_time)
{
    m_current_test->onUpdate(frame_time);
}

void TestingEnvironment::onImGuiUpdate()
{
    if (m_current_test == &m_empty_test) {
        ImGui::Begin("Tests");

        for (auto& kv : m_tests) {
            if (ImGui::Button(kv.first.c_str())) {
                loadTest(kv.first);
            }
        }

        ImGui::End();
    }
    else {
        m_current_test->_onImGuiUpdate();
    }
}
