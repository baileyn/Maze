#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

class Camera
{
public:
	Camera(const glm::vec3& position);
	glm::mat4 getViewMatrix() const;

private:
	glm::vec3 m_position;
	float m_yaw;
	float m_pitch;
};

#endif // CAMERA_HPP