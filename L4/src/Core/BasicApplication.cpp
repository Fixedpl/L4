#include "BasicApplication.h"

#include "OpenGL/GL_Context.h"
#include "OpenGL/GL_Renderer.h"

BasicApplication::BasicApplication(const WindowSettings& window_settings)
    :
    Application(window_settings)
{
    m_window.create();

    OpenGL::Context::create();
    OpenGL::Renderer::init();
    OpenGL::Renderer::setClearColor(glm::vec4(0.6f, 0.4f, 0.3f, 1.0f));
}

void BasicApplication::run()
{
    loop();
}

void BasicApplication::loop()
{
    float current_time = static_cast<float>(glfwGetTime());

    while (m_window.isRunning())
    {
        OpenGL::Renderer::clear();

        float new_time = static_cast<float>(glfwGetTime());
        float frame_time = new_time - current_time;
        current_time = new_time;

        onUpdate(frame_time);

        m_window.swapBuffers();
    }

    m_window.shutdown();
}
