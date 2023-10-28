#include "Basic3DApplication.h"

#include "OpenGL/GL_Context.h"
#include "OpenGL/GL_Renderer.h"


Basic3DApplication::Basic3DApplication(const WindowSettings& window_settings)
    :
    Application(window_settings)
{
    m_window.create();

    OpenGL::Context::create();
    OpenGL::Renderer::init();
    OpenGL::Renderer::setClearColor(glm::vec4(0.6f, 0.4f, 0.3f, 1.0f));

    m_controller3D = new Controller3D(m_window);
}

void Basic3DApplication::run()
{
    loop();
}

void Basic3DApplication::loop()
{
    float current_time = static_cast<float>(glfwGetTime());

    while (m_window.isRunning())
    {
        OpenGL::Renderer::clear();

        float new_time = static_cast<float>(glfwGetTime());
        float frame_time = new_time - current_time;
        current_time = new_time;

        m_controller3D->handleCamera(frame_time);

        onUpdate(frame_time);

        m_window.swapBuffers();
    }

    m_window.shutdown();
}
