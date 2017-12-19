#include "MazeGame.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

MazeGame::MazeGame()
	: Game{ "Window title", 800, 600 }, m_triangle{ 0, 0, 0, 0 }
{
}

bool MazeGame::init()
{
	if (!gladLoadGL()) {
		return false;
	}

	m_shader.loadFromFile("Assets/vert.glsl", "Assets/frag.glsl");

	m_loader.add({ { 0, 1, 0 }, { 0, 1, 0 } });
	m_loader.add({ { 0, 0, 0 }, { 0, 1, 0 } });
	m_loader.add({ { 1, 1, 0 }, { 0, 1, 0 } });
	
	m_triangle = m_loader.build();

	glClearColor(1, 0, 0, 1);
	return true;
}

void MazeGame::render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	sf::Shader::bind(&m_shader);
	m_shader.setUniform("projection", sf::Glsl::Mat4{ glm::value_ptr(m_projection) });
	m_triangle.render();
	sf::Shader::bind(nullptr);
}

void MazeGame::handleWindowEvent(sf::Event& e)
{
	if (e.type == sf::Event::Resized) {
		glViewport(0, 0, e.size.width, e.size.height);

		m_projection = glm::perspective<float>(glm::radians(75.0f), static_cast<float>(e.size.width) / static_cast<float>(e.size.height), 0.001f, 1000.0f);
	}
}