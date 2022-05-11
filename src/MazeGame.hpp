#ifndef MAZEGAME_HPP
#define MAZEGAME_HPP
#pragma once

#include "Game.hpp"
#include "MeshLoader.hpp"
#include "Camera.hpp"

#include <SFML/Graphics.hpp>

#include <glm/glm.hpp>

class MazeGame : public Game
{
public:
	MazeGame();

protected:
	bool init() override;
	void update(sf::Time& delta) override;
	void render() override;
	void handleWindowEvent(sf::Event& e) override;
	void cleanup() override;

private:
	MeshLoader m_loader;
	Entity m_triangle;
	Entity m_terrain;
	sf::Shader m_shader;

	glm::mat4 m_projection;
	Camera m_camera;
};


#endif // MAZEGAME_HPP