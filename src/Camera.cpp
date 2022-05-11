#include "Camera.hpp"

#include <SFML/Window/Keyboard.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3& position)
	: m_position{ position }, m_yaw{ 0 }, m_pitch{ 0 }
{

}

void Camera::update(sf::Time& delta)
{
	float deltaZ = 0;
	float deltaY = 0;

	float speed = WALK_SPEED;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
		speed *= 4;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		deltaZ += delta.asSeconds() * speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		deltaZ -= delta.asSeconds() * speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		m_yaw -= delta.asSeconds() * TURN_SPEED;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		m_yaw += delta.asSeconds() * TURN_SPEED;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
		deltaY += delta.asSeconds() * speed;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
		deltaY -= delta.asSeconds() * speed;
	}

	float yaw = m_yaw - 90;

	glm::vec3 front{
		glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(m_pitch)),
		glm::sin(glm::radians(m_pitch)),
		glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(m_pitch))
	};

	front = glm::normalize(front);
	front *= deltaZ;

	m_position += front;
	m_position.y += deltaY;
}

void Camera::translate(float x, float y, float z)
{
	m_position.x += x;
	m_position.y += y;
	m_position.z += z;
}

glm::mat4 Camera::getViewMatrix() const
{
	float yaw = m_yaw - 90;

	glm::vec3 front{
		glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(m_pitch)),
		glm::sin(glm::radians(m_pitch)),
		glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(m_pitch))
	};

	front = glm::normalize(front);

	return glm::lookAt(m_position, m_position + front, { 0, 1, 0 });
}