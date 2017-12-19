#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/System/Time.hpp>
#include <glm/glm.hpp>

class Camera
{
public:
	static constexpr float WALK_SPEED = 10.0f;
	static constexpr float TURN_SPEED = 360.0f;

	Camera(const glm::vec3& position);	
	void update(sf::Time& delta);
	void translate(float x, float y, float z);

	glm::mat4 getViewMatrix() const;

private:
	glm::vec3 m_position;
	float m_yaw;
	float m_pitch;
};

#endif // CAMERA_HPP