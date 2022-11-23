#include <SFML/Graphics.hpp>
#include <vector>

int WinMain()
{
	std::srand(std::time(nullptr));
	sf::RenderWindow gameWindow;
	sf::RenderWindow picWindow;
	gameWindow.create(sf::VideoMode(600, 600), "");
	picWindow.create(sf::VideoMode(600, 600), "");
	gameWindow.setFramerateLimit(60);
	sf::Event event;

	while (gameWindow.isOpen() || picWindow.isOpen()) {
		while (gameWindow.pollEvent(event) || picWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				gameWindow.close();
				picWindow.close();
			}
		}

		gameWindow.clear();
		picWindow.clear();

		gameWindow.display();
		picWindow.display();
	}

	return 0;
}
