#include "Grid.h"

Grid::Grid(int SpawnPercentage) {
	for (int y = 0; y < ROWS; y++) {
		for (int x = 0; x < COLUMNS; x++) {
			gameGrid[y][x] = (rand() % 101) < SpawnPercentage ? 1 : 0;
			oldGrid[y][x] = gameGrid[y][x];
		}
	}
}

int Grid::CountNeighbors(int x, int y) {
	int yAbove = (y + 1) % ROWS;
	int yBelow = (y - 1 + ROWS) % ROWS;
	int xLeft = (x - 1 + COLUMNS) % COLUMNS;
	int xRight = (x + 1) % COLUMNS;
	return oldGrid[yAbove][xLeft] +
		oldGrid[yAbove][x] +
		oldGrid[yAbove][xRight] +
		oldGrid[y][xLeft] +
		oldGrid[y][xRight] +
		oldGrid[yBelow][xLeft] +
		oldGrid[yBelow][x] +
		oldGrid[yBelow][xRight];
}

void Grid::UpdateGrid() {
	int neighbors;
	for (int y = 0; y < ROWS; y++) {
		for (int x = 0; x < COLUMNS; x++) {
			neighbors = CountNeighbors(x, y);
			if (neighbors < 2 || neighbors > 3)
				gameGrid[y][x] = 0;
			else if (neighbors == 3)
				gameGrid[y][x] = 1;
		}
	}
	copyGrid();
}

void Grid::DrawGrid(sf::RenderWindow& window) {
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color::Black);
	rect.setSize({ GRIDSIZE,GRIDSIZE });
	for (int y = 0; y < ROWS; y++) {
		for (int x = 0; x < COLUMNS; x++) {
			if (gameGrid[y][x]) {
				rect.setPosition(x * GRIDSIZE, y * GRIDSIZE);
				window.draw(rect);
			}
		}
	}
}

void Grid::ToggleCell(sf::Vector2i pos) {
	if (pos.x < 0 || pos.x> WIDTH || pos.y< 0 || pos.y> HEIGHT)return;
	pos /= GRIDSIZE;
	gameGrid[pos.y][pos.x] = !gameGrid[pos.y][pos.x];
	oldGrid[pos.y][pos.x] = gameGrid[pos.y][pos.x];
}

void Grid::copyGrid() {
	for (int y = 0; y < ROWS; y++) {
		for (int x = 0; x < COLUMNS; x++) {
			oldGrid[y][x] = gameGrid[y][x];
		}
	}
}

void Grid::FillGrid() {
	for (int y = 0; y < ROWS; y++) {
		for (int x = 0; x < COLUMNS; x++) {
			gameGrid[y][x] = (rand() % 101) < 50 ? 1 : 0;
			oldGrid[y][x] = gameGrid[y][x];
		}
	}
}
