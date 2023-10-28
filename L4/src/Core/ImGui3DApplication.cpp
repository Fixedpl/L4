#include "ImGui3DApplication.h"

#include "OpenGL/GL_Context.h"
#include "OpenGL/GL_Renderer.h"


ImGui3DApplication::ImGui3DApplication(const WindowSettings& window_settings)
    :
    Application(window_settings)
{
    m_window.create();

    OpenGL::Context::create();
    OpenGL::Renderer::init();
    OpenGL::Renderer::setClearColor(glm::vec4(0.6f, 0.4f, 0.3f, 1.0f));

    m_controller3D = new Controller3D(m_window);

    imGuiInit();
}

void ImGui3DApplication::run()
{
    loop();
}

void ImGui3DApplication::loop()
{
    float current_time = static_cast<float>(glfwGetTime());

    while (m_window.isRunning())
    {
        OpenGL::Renderer::clear();

        imGuiNewFrame();

        float new_time = static_cast<float>(glfwGetTime());
        float frame_time = new_time - current_time;
        current_time = new_time;

        m_controller3D->handleCamera(frame_time);

        onUpdate(frame_time);
        onImGuiUpdate();

        imGuiRender();

        m_window.swapBuffers();
    }

    imGuiShutdown();

    m_window.shutdown();
}

void ImGui3DApplication::imGuiInit()
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

void ImGui3DApplication::imGuiNewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGui3DApplication::imGuiRender()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGui3DApplication::imGuiShutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}