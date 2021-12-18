#pragma once
#include "Constants.h"
#include "SFML/Graphics.hpp"

class Grid
{
public:
	Grid(int SpawnPercentage);
	void UpdateGrid();
	void DrawGrid(sf::RenderWindow& window);
	void ToggleCell(sf::Vector2i pos);
	void FillGrid();
private:
	void copyGrid();
	int CountNeighbors(int x, int y);
	int oldGrid[HEIGHT / GRIDSIZE][WIDTH / GRIDSIZE];
	int gameGrid[HEIGHT / GRIDSIZE][WIDTH / GRIDSIZE];
};

