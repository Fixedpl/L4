#include "Controller3D.h"

#include <glm/gtc/matrix_transform.hpp>


Controller3D::Controller3D(Window& window)
    :
    m_window(window),
    m_keyboard(window.getKeyboardInput()),
    m_mouse(window.getMouseInput()),
    m_pos(0.0f),
    m_movement_speed(5.0f),
    m_flying_mode(false),
    m_view(1.0f)
{
    WindowSettings window_settings = window.getWindowSettings();
    m_perspective = glm::perspective(glm::radians(60.0f), (float)window_settings.width / window_settings.height, 0.1f, 100.0f);
    calculateMvp(glm::vec3(0.0f, 0.0f, -1.0f));
}

const glm::mat4& Controller3D::mvp() const
{
    return m_mvp;
}

float Controller3D::getMovementSpeed() const
{
    return m_movement_speed;
}

void Controller3D::setMovementSpeed(const float& speed)
{
    m_movement_speed = speed;
}

glm::vec3 Controller3D::getPosition() const
{
    return m_pos;
}

void Controller3D::setPosition(const glm::vec3& position)
{
    m_pos = position;
    calculateMvp(glm::vec3(0.0f, 0.0f, -1.0f));
}

void Controller3D::handleCamera(const float& dt)
{
    handleFlyingMode();
    if (m_flying_mode) {
        glm::vec3 direction_vector = handleCameraMouse();
        handleCameraKeyboard(dt, direction_vector);

        calculateMvp(direction_vector);
    }
}

glm::vec3 Controller3D::handleCameraMouse()
{
    glm::vec2 mouse_pos = m_mouse->getLastCursorPosition();
    return m_3d_mouse_controller.registerMouseMovement(mouse_pos);
}

void Controller3D::handleCameraKeyboard(const float& dt, const glm::vec3& direction)
{
    if (m_keyboard->isKeyPressed(KeyCode::KEY_W)) {
        m_pos += dt * m_movement_speed * direction;
    }
    if (m_keyboard->isKeyPressed(KeyCode::KEY_S)) {
        m_pos -= dt * m_movement_speed * direction;
    }
    if (m_keyboard->isKeyPressed(KeyCode::KEY_A)) {
        m_pos -= dt * glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f))) * m_movement_speed;
    }
    if (m_keyboard->isKeyPressed(KeyCode::KEY_D)) {
        m_pos += dt * glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f))) * m_movement_speed;
    }
}

void Controller3D::handleFlyingMode()
{
    if (m_window.getKeyboardInput()->isKeyPressed(KeyCode::KEY_ESCAPE)) {
        setFlyingMode(false);
    }
    if (m_window.getMouseInput()->isRightButtonPressed()) {
        m_3d_mouse_controller.registerNextMoveAsFirst();
        setFlyingMode(true);
    }
}

void Controller3D::setFlyingMode(bool value)
{
    m_flying_mode = value;
    m_window.setCursorCapture(value);
}

void Controller3D::calculateMvp(const glm::vec3& direction_vector)
{
    m_view = glm::lookAt(m_pos, m_pos + direction_vector, glm::vec3(0.0f, 1.0f, 0.0f));
    m_mvp = m_perspective * m_view;
}
