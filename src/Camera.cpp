#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3& position)
	: m_position{ position }, m_yaw{ 0 }, m_pitch{ 0 }
{

}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(m_position, { 0, 0, 0 }, { 0, 1, 0 });
}