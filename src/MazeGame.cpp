#include "MazeGame.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <array>
#include <stack>
#include <random>

namespace
{
std::random_device random_device{};
std::mt19937 random_engine{random_device()};

Cell::Direction randomDirection(const Cell *cell)
{
	std::vector<Cell::Direction> directions{};

	if (!cell->hasDirectionBeenSearched(Cell::Direction::FRONT))
	{
		directions.push_back(Cell::Direction::FRONT);
	}

	if (!cell->hasDirectionBeenSearched(Cell::Direction::BACK))
	{
		directions.push_back(Cell::Direction::BACK);
	}

	if (!cell->hasDirectionBeenSearched(Cell::Direction::RIGHT))
	{
		directions.push_back(Cell::Direction::RIGHT);
	}

	if (!cell->hasDirectionBeenSearched(Cell::Direction::LEFT))
	{
		directions.push_back(Cell::Direction::LEFT);
	}

	if (directions.size() == 1)
	{
		return directions.at(0);
	}

	return directions.at(random_engine() % directions.size());
}

constexpr Cell::Direction reverseDirection(Cell::Direction direction)
{
	switch (direction)
	{
	case Cell::Direction::FRONT:
		return Cell::Direction::BACK;
	case Cell::Direction::BACK:
		return Cell::Direction::FRONT;
	case Cell::Direction::LEFT:
		return Cell::Direction::RIGHT;
	case Cell::Direction::RIGHT:
		return Cell::Direction::LEFT;
	default:
		throw std::runtime_error{"Invalid direction"};
	}
}

constexpr Cell::Direction getDirectionFromVector(const glm::vec2 &vector)
{
	if (vector.x < 0)
	{
		return Cell::Direction::LEFT;
	}
	else if (vector.x > 0)
	{
		return Cell::Direction::RIGHT;
	}

	if (vector.y < 0)
	{
		return Cell::Direction::BACK;
	}
	else if (vector.y > 0)
	{
		return Cell::Direction::FRONT;
	}

	throw std::runtime_error{"Invalid direction vector."};
}

float getCellBoundary(const Cell &cell, const Cell::Direction &direction)
{
	// First determine if there's possibly a wall in that direction to block us.
	if (!cell.hasWall(direction))
	{
		return -1.0f;
	}

	// A wall exists, so calculate the maximum/minimum we for that cell in that direction.
	switch (direction)
	{
	case Cell::Direction::FRONT:
		return -(static_cast<int>(cell.getZ()) + 1) * Cell::WIDTH;
	case Cell::Direction::BACK:
		return -static_cast<int>(cell.getZ()) * Cell::WIDTH;
	case Cell::Direction::LEFT:
		return cell.getX() * Cell::WIDTH;
	case Cell::Direction::RIGHT:
		return (cell.getX() + 1) * Cell::WIDTH;
	default:
		throw std::runtime_error{"Invalid direction specified."};
	}
}
}

MazeGame::MazeGame()
	: Game{"Window title", 800, 600, sf::ContextSettings(24, 8, 4, 3, 3)}, m_triangle{0, 0, 0, 0},
	  m_camera{{Cell::WIDTH / 2.0f, 1.7f, Cell::HEIGHT / -2.0f}}, m_start{0, 0}, m_end{WIDTH - 1, HEIGHT - 1}
{
	for (size_t x = 0; x < WIDTH; x++)
	{
		for (size_t z = 0; z < HEIGHT; z++)
		{
			auto &cell = m_cells.at(x + z * WIDTH);
			cell.setLocation(x, z);

			if (x == 0)
			{
				cell.markSearched(Cell::Direction::LEFT);
			}
			else if (x == WIDTH - 1)
			{
				cell.markSearched(Cell::Direction::RIGHT);
			}

			if (z == 0)
			{
				cell.markSearched(Cell::Direction::BACK);
			}
			else if (z == HEIGHT - 1)
			{
				cell.markSearched(Cell::Direction::FRONT);
			}
		}
	}

	std::stack<Cell *> cells;

	Cell *currentCell = &m_cells.at(m_cells.size() - 1);
	currentCell->visit();

	do
	{
		auto x = currentCell->getX();
		auto z = currentCell->getZ();

		if (currentCell->hasBeenSearched())
		{
			currentCell = cells.top();
			cells.pop();
			continue;
		}

		auto direction = randomDirection(currentCell);

		Cell *destination = nullptr;

		switch (direction)
		{
		case Cell::Direction::FRONT:
			if (z + 1 < HEIGHT)
			{
				destination = &m_cells.at(x + (z + 1) * WIDTH);
			}
			else
			{
				continue;
			}
			break;
		case Cell::Direction::BACK:
			if (z - 1 >= 0)
			{
				destination = &m_cells.at(x + (z - 1) * WIDTH);
			}
			else
			{
				continue;
			}
			break;
		case Cell::Direction::LEFT:
			if (x - 1 >= 0)
			{
				destination = &m_cells.at((x - 1) + z * WIDTH);
			}
			else
			{
				continue;
			}
			break;
		case Cell::Direction::RIGHT:
			if (x + 1 < WIDTH)
			{
				destination = &m_cells.at((x + 1) + z * WIDTH);
			}
			else
			{
				continue;
			}
			break;
		default:
			throw std::runtime_error{"Invalid Direction"};
		}

		if (destination->hasBeenVisited())
		{
			currentCell->markSearched(direction);
			continue;
		}

		currentCell->markSearched(direction);
		currentCell->destroyWall(direction);
		destination->visit();
		destination->markSearched(reverseDirection(direction));
		destination->destroyWall(reverseDirection(direction));

		cells.push(currentCell);
		currentCell = destination;
	} while (!cells.empty());
}

bool MazeGame::init()
{
	if (!gladLoadGL())
	{
		return false;
	}

	m_shader.loadFromFile("Assets/vert.glsl", "Assets/frag.glsl");

	for (size_t x = 0; x < WIDTH; x++)
	{
		for (size_t z = 0; z < HEIGHT; z++)
		{
			auto &cell = m_cells.at(x + z * WIDTH);

			glm::vec3 color{
				(random_engine() % 255) / 255.0f,
				(random_engine() % 255) / 255.0f,
				(random_engine() % 255) / 255.0f};

			glm::vec3 floorColor{
				0.5, 0.5, 0.5};

			if (x == m_start.x && z == m_start.y)
			{
				color.r = 0;
				color.g = 1;
				color.b = 0;
			}
			else if (x == m_end.x && z == m_end.y)
			{
				color.r = 1;
				color.g = 0;
				color.b = 0;
			}

			float cellX = x * Cell::WIDTH;
			float cellZ = -(z * Cell::WIDTH);

			// Add the floor of the cell
			m_loader.add({{cellX, 0, cellZ - Cell::WIDTH}, floorColor});
			m_loader.add({{cellX, 0, cellZ}, floorColor});
			m_loader.add({{cellX + Cell::WIDTH, 0, cellZ - Cell::WIDTH}, floorColor});
			m_loader.add({{cellX + Cell::WIDTH, 0, cellZ - Cell::WIDTH}, floorColor});
			m_loader.add({{cellX, 0, cellZ}, floorColor});
			m_loader.add({{cellX + Cell::WIDTH, 0, cellZ}, floorColor});

			// Add the left wall if necessary.
			if (cell.hasWall(Cell::Direction::LEFT))
			{
				m_loader.add({{cellX, Cell::HEIGHT, cellZ}, color});
				m_loader.add({{cellX, 0, cellZ}, color});
				m_loader.add({{cellX, Cell::HEIGHT, cellZ - Cell::WIDTH}, color});
				m_loader.add({{cellX, Cell::HEIGHT, cellZ - Cell::WIDTH}, color});
				m_loader.add({{cellX, 0, cellZ}, color});
				m_loader.add({{cellX, 0, cellZ - Cell::WIDTH}, color});
			}

			// Add the right wall if necessary.
			if (cell.hasWall(Cell::Direction::RIGHT))
			{
				m_loader.add({{cellX + Cell::WIDTH, Cell::HEIGHT, cellZ - Cell::WIDTH}, color});
				m_loader.add({{cellX + Cell::WIDTH, 0, cellZ - Cell::WIDTH}, color});
				m_loader.add({{cellX + Cell::WIDTH, Cell::HEIGHT, cellZ}, color});
				m_loader.add({{cellX + Cell::WIDTH, Cell::HEIGHT, cellZ}, color});
				m_loader.add({{cellX + Cell::WIDTH, 0, cellZ - Cell::WIDTH}, color});
				m_loader.add({{cellX + Cell::WIDTH, 0, cellZ}, color});
			}

			// Add the front wall if necessary.
			if (cell.hasWall(Cell::Direction::FRONT))
			{
				m_loader.add({{cellX, Cell::HEIGHT, cellZ - Cell::WIDTH}, color});
				m_loader.add({{cellX, 0, cellZ - Cell::WIDTH}, color});
				m_loader.add({{cellX + Cell::WIDTH, Cell::HEIGHT, cellZ - Cell::WIDTH}, color});
				m_loader.add({{cellX + Cell::WIDTH, Cell::HEIGHT, cellZ - Cell::WIDTH}, color});
				m_loader.add({{cellX, 0, cellZ - Cell::WIDTH}, color});
				m_loader.add({{cellX + Cell::WIDTH, 0, cellZ - Cell::WIDTH}, color});
			}

			// Add the back wall if necessary.
			if (cell.hasWall(Cell::Direction::BACK))
			{
				m_loader.add({{cellX + Cell::WIDTH, Cell::HEIGHT, cellZ}, color});
				m_loader.add({{cellX + Cell::WIDTH, 0, cellZ}, color});
				m_loader.add({{cellX, Cell::HEIGHT, cellZ}, color});
				m_loader.add({{cellX, Cell::HEIGHT, cellZ}, color});
				m_loader.add({{cellX + Cell::WIDTH, 0, cellZ}, color});
				m_loader.add({{cellX, 0, cellZ}, color});
			}

			// Add the ceiling.
			/*m_loader.add({ { cellX, Cell::HEIGHT, cellZ - Cell::WIDTH }, color }); // 1
			m_loader.add({ { cellX + Cell::WIDTH, Cell::HEIGHT, cellZ - Cell::WIDTH }, color }); // 3
			m_loader.add({ { cellX, Cell::HEIGHT, cellZ }, color }); // 2
			m_loader.add({ { cellX, Cell::HEIGHT, cellZ }, color }); // 2
			m_loader.add({ { cellX + Cell::WIDTH, Cell::HEIGHT, cellZ - Cell::WIDTH }, color }); // 3
			m_loader.add({ { cellX + Cell::WIDTH, Cell::HEIGHT, cellZ }, color }); // 4*/
		}
	}

	m_triangle = m_loader.build();

	// By default the Camera points down the X axis, rotate it to point down the Z axis.
	m_camera.rotateY(-90);

	auto size = window().getSize();
	glViewport(0, 0, size.x, size.y);
	m_projection = glm::perspective<float>(glm::radians(45.0f), static_cast<float>(size.x) / static_cast<float>(size.y), 0.001f, 1000.0f);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);
	return true;
}

void MazeGame::update(sf::Time &delta)
{
	updateCamera(delta);
}

void MazeGame::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	sf::Shader::bind(&m_shader);
	m_shader.setUniform("projection", sf::Glsl::Mat4{glm::value_ptr(m_projection)});
	m_shader.setUniform("view", sf::Glsl::Mat4{glm::value_ptr(m_camera.getViewMatrix())});
	m_triangle.render();
	sf::Shader::bind(nullptr);
}

void MazeGame::handleWindowEvent(sf::Event &e)
{
	if (e.type == sf::Event::Resized)
	{
		glViewport(0, 0, e.size.width, e.size.height);
		m_projection = glm::perspective<float>(glm::radians(45.0f), static_cast<float>(e.size.width) / static_cast<float>(e.size.height), 0.001f, 1000.0f);
	}
}

void MazeGame::cleanup()
{
	m_triangle.cleanup();
}

void MazeGame::updateCamera(sf::Time &delta)
{
	float deltaZ = 0;
	float deltaY = 0;

	float speed = Camera::WALK_SPEED;
	float deltaYaw = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{
		speed *= 4;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		deltaZ += delta.asSeconds() * speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		deltaZ -= delta.asSeconds() * speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		deltaYaw -= delta.asSeconds() * Camera::TURN_SPEED;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		deltaYaw += delta.asSeconds() * Camera::TURN_SPEED;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		deltaY += delta.asSeconds() * speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		deltaY -= delta.asSeconds() * speed;
	}

	m_camera.rotateY(deltaYaw);
	float yaw = m_camera.getYaw();

	glm::vec3 front{
		static_cast<float>(glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(m_camera.getPitch()))),
		static_cast<float>(glm::sin(glm::radians(m_camera.getPitch()))),
		static_cast<float>(glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(m_camera.getPitch())))};

	front = glm::normalize(front);
	front *= deltaZ;

	auto location = m_camera.getLocation();
	glm::vec3 destinationLocation{location.x + front.x, location.y + front.y + deltaY, location.z + front.z};

	if (deltaZ != 0)
	{
		// Collision detection isn't important unless we're moving.

		// Calculate cellX and cellY
		unsigned int cellX = static_cast<int>(location.x / Cell::WIDTH);
		unsigned int cellZ = static_cast<int>(-location.z / Cell::WIDTH);
		auto cell = m_cells.at(cellX + cellZ * WIDTH);

		// Check foward boundary
		float boundary = getCellBoundary(cell, Cell::Direction::FRONT);
		if (boundary != -1.0f)
		{
			if (destinationLocation.z < boundary)
			{
				destinationLocation.z = boundary + 0.01f;
			}
		}

		// Check back boundary
		boundary = getCellBoundary(cell, Cell::Direction::BACK);
		if (boundary != -1.0f)
		{
			if (destinationLocation.z > boundary)
			{
				destinationLocation.z = boundary - 0.01f;
			}
		}

		// Check left boundary
		boundary = getCellBoundary(cell, Cell::Direction::LEFT);
		if (boundary != -1.0f)
		{
			if (destinationLocation.x < boundary)
			{
				destinationLocation.x = boundary + 0.01f;
			}
		}

		boundary = getCellBoundary(cell, Cell::Direction::RIGHT);
		if (boundary != -1.0f)
		{
			if (destinationLocation.x > boundary)
			{
				destinationLocation.x = boundary - 0.01f;
			}
		}
	}

	m_camera.setLocation(destinationLocation);
}