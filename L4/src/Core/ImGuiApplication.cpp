#include "ImGuiApplication.h"

#include "OpenGL/GL_Context.h"
#include "OpenGL/GL_Renderer.h"


ImGuiApplication::ImGuiApplication(const WindowSettings& window_settings)
    :
    Application(window_settings)
{
    m_window.create();

    OpenGL::Context::create(window_settings.opengl_debug);
    OpenGL::Renderer::init();
    OpenGL::Renderer::setClearColor(glm::vec4(0.6f, 0.4f, 0.3f, 1.0f));

    imGuiInit();
}

void ImGuiApplication::run()
{
    loop();
}

void ImGuiApplication::loop()
{
    float current_time = static_cast<float>(glfwGetTime());

    while (m_window.isRunning())
    {
        OpenGL::Renderer::clear();

        imGuiNewFrame();

        float new_time = static_cast<float>(glfwGetTime());
        float frame_time = new_time - current_time;
        current_time = new_time;

        onUpdate(frame_time);
        onImGuiUpdate();

        imGuiRender();

        m_window.swapBuffers();
    }

    imGuiShutdown();

    m_window.shutdown();
}

void ImGuiApplication::imGuiInit()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_window.getNative(), true);
    const WindowSettings& window_settings = m_window.getWindowSettings();
    std::string glsl_version =
        "#version " +
        std::to_string(window_settings.opengl_major_version) +
        std::to_string(window_settings.opengl_minor_version) +
        "0";
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());
}

void ImGuiApplication::imGuiNewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiApplication::imGuiRender()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiApplication::imGuiShutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
