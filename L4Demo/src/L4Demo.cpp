#include <iostream>

#include "OpenGL/GL_gl.h"
#include "OpenGL/GL_Renderer.h"


void glfwError(int id, const char* description)
{
    std::cout << description << std::endl;
}

int main()
{
    glfwSetErrorCallback(glfwError);
    if (!glfwInit()) {
        std::cout << "ERROR: Couldn't initialize GLFW." << std::endl;
    }

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    GLFWwindow* m_window = glfwCreateWindow(1280, 720, "L4", NULL, NULL);
    if (!m_window) {
        glfwTerminate();
        std::cout << "ERROR: Couldn't create window." << std::endl;
    }

    glfwMakeContextCurrent(m_window);

    float current_time = static_cast<float>(glfwGetTime());

    if (glewInit() != GLEW_OK) {
        std::cout << "ERROR: Couldnt initialize GLEW" << std::endl;
    }

    OpenGL::Renderer::setClearColor(glm::vec4(0.6f, 0.4f, 0.3f, 1.0f));
    
    while (!glfwWindowShouldClose(m_window))
    {
        OpenGL::Renderer::clear();

        
        float new_time = static_cast<float>(glfwGetTime());
        float frame_time = new_time - current_time;
        current_time = new_time;

        //

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }


    glfwTerminate();

}

