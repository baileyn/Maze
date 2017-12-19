#include "MazeGame.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

MazeGame::MazeGame()
	: Game{ "Window title", 800, 600, sf::ContextSettings(24, 8, 4, 3, 3) }, m_triangle{ 0, 0, 0, 0 }, 
	m_camera { { 0, 1.7f, 0 } }, m_start{ 0, 0 }, m_end{ WIDTH - 1, HEIGHT -1 }
{
	for (size_t x = 0; x < WIDTH; x++) {
		for (size_t z = 0; z < HEIGHT; z++) {
			auto& cell = m_cells.at(x + z * WIDTH);

			// Initialize the cells
		}
	}
}

bool MazeGame::init()
{
	if (!gladLoadGL()) {
		return false;
	}

	m_shader.loadFromFile("Assets/vert.glsl", "Assets/frag.glsl");

	for (size_t x = 0; x < WIDTH; x++) {
		for (size_t z = 0; z < HEIGHT; z++) {
			auto& cell = m_cells.at(x + z * WIDTH);

			glm::vec3 color{ 0, 0, 1 };

			if (x == m_start.x && z == m_start.y) {
				color.r = 0;
				color.g = 1;
				color.b = 0;
			}
			else if (x == m_end.x && z == m_end.y) {
				color.r = 1;
				color.g = 0;
				color.b = 0;
			}

			float cellX = x * Cell::WIDTH;
			float cellZ = -(z * Cell::WIDTH);

			// Add the floor of the cell
			m_loader.add({ { cellX, 0, cellZ - Cell::WIDTH }, color });
			m_loader.add({ { cellX, 0, cellZ }, color });
			m_loader.add({ { cellX + Cell::WIDTH, 0, cellZ - Cell::WIDTH }, color });
			m_loader.add({ { cellX + Cell::WIDTH, 0, cellZ - Cell::WIDTH }, color });
			m_loader.add({ { cellX, 0, cellZ }, color });
			m_loader.add({ { cellX + Cell::WIDTH, 0, cellZ }, color });

			// Add the left wall if necessary.
			if (cell.hasWall(Cell::Direction::LEFT)) {
				m_loader.add({ { cellX, Cell::HEIGHT, cellZ }, color });
				m_loader.add({ { cellX, 0, cellZ }, color });
				m_loader.add({ { cellX, Cell::HEIGHT, cellZ - Cell::WIDTH }, color });
				m_loader.add({ { cellX, Cell::HEIGHT, cellZ - Cell::WIDTH }, color });
				m_loader.add({ { cellX, 0, cellZ }, color });
				m_loader.add({ { cellX, 0, cellZ - Cell::WIDTH }, color });
			}

			// Add the right wall if necessary.
			if (cell.hasWall(Cell::Direction::RIGHT)) {
				m_loader.add({ { cellX + Cell::WIDTH, Cell::HEIGHT, cellZ - Cell::WIDTH }, color });
				m_loader.add({ { cellX + Cell::WIDTH, 0, cellZ - Cell::WIDTH }, color });
				m_loader.add({ { cellX + Cell::WIDTH, Cell::HEIGHT, cellZ }, color });
				m_loader.add({ { cellX + Cell::WIDTH, Cell::HEIGHT, cellZ }, color });
				m_loader.add({ { cellX + Cell::WIDTH, 0, cellZ - Cell::WIDTH }, color });
				m_loader.add({ { cellX + Cell::WIDTH, 0, cellZ }, color });
			}
		}
	}

	m_triangle = m_loader.build();

	auto size = window().getSize();
	glViewport(0, 0, size.x, size.y);
	m_projection = glm::perspective<float>(glm::radians(45.0f), static_cast<float>(size.x) / static_cast<float>(size.y), 0.001f, 1000.0f);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);
	return true;
}

void MazeGame::update(sf::Time& delta)
{
	m_camera.update(delta);
}

void MazeGame::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	sf::Shader::bind(&m_shader);
	m_shader.setUniform("projection", sf::Glsl::Mat4{ glm::value_ptr(m_projection) });
	m_shader.setUniform("view", sf::Glsl::Mat4{ glm::value_ptr(m_camera.getViewMatrix()) });
	m_triangle.render();
	sf::Shader::bind(nullptr);
}

void MazeGame::handleWindowEvent(sf::Event& e)
{
	if (e.type == sf::Event::Resized) {
		glViewport(0, 0, e.size.width, e.size.height);
		m_projection = glm::perspective<float>(glm::radians(45.0f), static_cast<float>(e.size.width) / static_cast<float>(e.size.height), 0.001f, 1000.0f);
	}
}

void MazeGame::cleanup()
{
	m_triangle.cleanup();
}