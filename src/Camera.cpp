#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Camera::Camera(const glm::vec3& position)
	: m_position{ position }, m_yaw{ 0 }, m_pitch{ 0 }
{

}

glm::mat4 Camera::getViewMatrix() const
{
	float yaw = m_yaw - 90;

	glm::vec3 front{
		glm::cos(glm::radians(yaw) * glm::cos(glm::radians(m_pitch))),
		glm::sin(glm::radians(m_pitch)),
		glm::sin(glm::radians(yaw) * glm::cos(glm::radians(m_pitch)))
	};

	front = glm::normalize(front);

	return glm::lookAt(m_position, m_position + front, { 0, 1, 0 });
}