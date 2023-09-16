#include "Mouse3DController.h"

Mouse3DController::Mouse3DController()
    :
    m_first_mouse_move(true),
    m_yaw(-90.0f),
    m_pitch(0.0f),
    m_sensitivity(0.2f),
    m_last_mouse_pos(0.0f)
{
}

glm::vec3 Mouse3DController::registerMouseMovement(const glm::vec2& pos)
{
    if (m_first_mouse_move)
    {
        m_last_mouse_pos = pos;
        m_first_mouse_move = false;
    }

    glm::vec2 offset = glm::vec2(
        pos.x - m_last_mouse_pos.x,
        m_last_mouse_pos.y - pos.y
    );

    m_last_mouse_pos = pos;

    offset *= m_sensitivity;

    m_yaw += offset.x;
    m_pitch += offset.y;

    if (m_pitch > 89.0f)
        m_pitch = 89.0f;
    if (m_pitch < -89.0f)
        m_pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    return glm::normalize(direction);
}

float Mouse3DController::getSensitivity() const
{
    return m_sensitivity;
}

void Mouse3DController::setSensitivity(const float& sens)
{
    m_sensitivity = sens;
}

void Mouse3DController::registerNextMoveAsFirst()
{
    m_first_mouse_move = true;
}
