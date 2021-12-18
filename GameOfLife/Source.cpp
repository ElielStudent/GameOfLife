#include <SFML/Graphics.hpp>
#include "Grid.h"
#include <iostream>
using namespace sf;

int SpawnPercentage;

void Menu() {
	std::string input;
	printf("------------GAME OF LIFE------------\n");
	printf("Press spacebar to toggle auto mode.\n");
	printf("Press backspace to repopulate.\n");
	printf("Press any other key to move a step.\n");
	printf("Click on the screen to toggle a cell.\n");
	printf("Please input the initial spawn percentage (default is 40).\n");
	std::cin >> SpawnPercentage;
	if (!std::cin)SpawnPercentage = 40;
}

int main() {
	Menu();
	RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Game of life wooo");
	window.setFramerateLimit(20);
	Grid* grid = new Grid(SpawnPercentage);
	while (window.isOpen()) {
		int toggle = 0;
		window.clear(Color::White);
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyReleased) {
				if (event.key.code == Keyboard::Space)
					toggle = !toggle;
				else if (event.key.code == Keyboard::BackSpace)
					grid->FillGrid();
				else
					grid->UpdateGrid();
			}
			if (Mouse::isButtonPressed(Mouse::Left)) {
				grid->ToggleCell(Mouse::getPosition(window));
			}
		}
		if (toggle)
			grid->UpdateGrid();
		grid->DrawGrid(window);
		window.display();
	}

	return 0;
}