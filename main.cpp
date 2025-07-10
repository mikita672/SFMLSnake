#include <SFML/Graphics.hpp>
#include "map.h"
#include "snake.h"
#include <cstdlib>
#include <ctime>

int main() {
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	sf::Clock clock;

	Snake m_player("Resources/Sprites/Snake");
	Map m_map("Resources/Sprites/Map/Full_map_32.png",
		"Resources/Sprites/Map/Full_map_32.png");

	sf::RenderWindow window(sf::VideoMode({ 512, 512 }), "SNAKE!");

	while (window.isOpen()) {

		while (const std::optional event = window.pollEvent()) {
			// Compare against the new scoped enum value
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		window.clear();
		m_map.drawMap(&window);
		m_map.run(&clock, &window, &m_player);
		window.display();
	}

	return 0;
}
