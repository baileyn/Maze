#include "MazeGame.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

void addNumber(std::vector<int>& numbers, std::vector<int>& indices, int i)
{
	auto location = std::find(std::begin(numbers), std::end(numbers), i);

	if (location == std::end(numbers)) {
		// If the location wasn't found, append it to the numbers vector
		numbers.push_back(i);

		// Also add a new entry for this index.
		indices.push_back(numbers.size() - 1);
	}
	else {
		// Otherwise, if it was found, add the index to the indices
		indices.push_back(location - std::begin(numbers));
	}
}

int main(int argc, char** argv)
{
    MazeGame game{};
    game.run();

	return 0;
}