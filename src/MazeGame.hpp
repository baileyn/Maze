#ifndef MAZEGAME_HPP
#define MAZEGAME_HPP
#pragma once

#include "Cell.hpp"
#include "Game.hpp"
#include "MeshLoader.hpp"
#include "Camera.hpp"

#include <SFML/Graphics.hpp>

#include <glm/glm.hpp>

#include <array>

class MazeGame : public Game
{
public:
	/**
	 * @brief the width of the Maze in Cells.
	 */
	static constexpr size_t WIDTH = 8;

	/**
	 * @brief the height (depth) of the Maze in Cells.
	 */
	static constexpr size_t HEIGHT = 8;

	/**
	 * @brief constructs a new MazeGame.
	 */
	MazeGame();

protected:
	bool init() override;
	void update(sf::Time& delta) override;
	void render() override;
	void handleWindowEvent(sf::Event& e) override;
	void cleanup() override;

private:
	void updateCamera(sf::Time& delta);

	MeshLoader m_loader;
	Entity m_triangle;
	sf::Shader m_shader;
	
	std::array<Cell, WIDTH * HEIGHT> m_cells;

	glm::mat4 m_projection;
	Camera m_camera;

	glm::vec2 m_start;
	glm::vec2 m_end;
};


#endif // MAZEGAME_HPP