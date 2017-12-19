#include "MazeGame.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

MazeGame::MazeGame()
	: Game{ "Window title", 800, 600 }, m_triangle{ 0, 0, 0, 0 }, m_camera{ { 0, 5, 5 } }
{
}

bool MazeGame::init()
{
	if (!gladLoadGL()) {
		return false;
	}

	m_shader.loadFromFile("Assets/vert.glsl", "Assets/frag.glsl");

	m_loader.add({ { -1, 1, 0 }, { 0, 1, 0 } });
	m_loader.add({ { -1, -1, 0 }, { 0, 1, 0 } });
	m_loader.add({ { 1, 1, 0 }, { 0, 1, 0 } });
	
	m_triangle = m_loader.build();

	auto size = window().getSize();
	glViewport(0, 0, size.x, size.y);
	m_projection = glm::perspective<float>(glm::radians(75.0f), static_cast<float>(size.x) / static_cast<float>(size.y), 0.001f, 1000.0f);

	glClearColor(0, 0, 0, 1);
	return true;
}

void MazeGame::render()
{
	glClear(GL_COLOR_BUFFER_BIT);

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
		printf("Window Resized: { %d, %d }\n", e.size.width, e.size.height);
		m_projection = glm::perspective<float>(glm::radians(75.0f), static_cast<float>(e.size.width) / static_cast<float>(e.size.height), 0.001f, 1000.0f);
	}
}

void MazeGame::cleanup()
{
	m_triangle.cleanup();
}