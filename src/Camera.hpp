#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/System/Time.hpp>
#include <glm/glm.hpp>

class Camera
{
public:
	/**
	 * The speed that the Camera moves around.
	 */
	static constexpr float WALK_SPEED = 10.0f;

	/**
	 * The speed that the Camera turns.
	 */
	static constexpr float TURN_SPEED = 360.0f;

	/**
	 * Constructs a new Camera at the specified location looking down the -z axis.
	 * 
	 * @param position the position that the Camera is currently located.
	 */
	Camera(const glm::vec3& position);	

	/**
	 * Update the internal state of the Camera.
	 * 
	 * @param delta the time elapsed since the last update.
	 */
	void update(sf::Time& delta);

	/**
	 * Manually moves the Camera by the specified unites.
	 * 
	 * @param x the amount of units to move on the x axis.
	 * @param y the amount of units to move on the y axis.
	 * @param z the amount of units to move on the z axis.
	 */
	void translate(float x, float y, float z);

	/**
	 * Constructs and returns the view matrix that represents this Camera.
	 * 
	 * @return the view matrix that represents this Camera.
	 */
	glm::mat4 getViewMatrix() const;

private:
	glm::vec3 m_position;
	float m_yaw;
	float m_pitch;
};

#endif // CAMERA_HPP