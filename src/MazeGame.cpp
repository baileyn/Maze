#include "MazeGame.hpp"

#include <glad/glad.h>

MazeGame::MazeGame()
	: Game{ "Window title", 800, 600 }
{
}

bool MazeGame::init()
{
	if (!gladLoadGL()) {
		return false;
	}

	glClearColor(1, 0, 0, 1);
	return true;
}

void MazeGame::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
}