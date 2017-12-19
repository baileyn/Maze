#include "Camera.hpp"

#include <SFML/Window/Keyboard.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3& position)
	: m_position{ position }, m_yaw{ 0 }, m_pitch{ 0 }
{

}

void Camera::translate(float x, float y, float z)
{
	m_position.x += x;
	m_position.y += y;
	m_position.z += z;
}

void Camera::setYaw(float yaw)
{
	m_yaw = yaw;
}

void Camera::rotateY(float r)
{
	m_yaw += r;
}

float Camera::getYaw() const
{
	return m_yaw;
}

float Camera::getPitch() const
{
	return m_pitch;
}

glm::mat4 Camera::getViewMatrix() const
{
	float yaw = m_yaw;

	glm::vec3 front{
		glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(m_pitch)),
		glm::sin(glm::radians(m_pitch)),
		glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(m_pitch))
	};

	front = glm::normalize(front);

	return glm::lookAt(m_position, m_position + front, { 0, 1, 0 });
}

void Camera::setLocation(glm::vec3 position)
{
	m_position = position;
}

glm::vec3 Camera::getLocation() const
{
	return m_position;
}