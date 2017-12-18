#ifndef MAZEGAME_HPP
#define MAZEGAME_HPP
#pragma once

#include "Game.hpp"

class MazeGame : public Game
{
public:
	MazeGame();

protected:
	bool init() override;
	void render() override;
};


#endif // MAZEGAME_HPP