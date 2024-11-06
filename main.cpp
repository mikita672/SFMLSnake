#include "map.h"
#include "snake.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>

int main() {
  std::srand(time(NULL));

  sf::Clock clock;

  Snake m_player("Resources/Sprites/Snake/Full_snake32.png");
  Map m_map("Resources/Sprites/Map/Full_map_32.png",
            "Resources/Sprites/Map/Full_map_32.png");
  sf::RenderWindow window(sf::VideoMode(512, 512), "SNAKE!");
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();

    m_map.drawMap(&window);
    m_player.snakeMovement(&clock);
    m_player.updateSnakeDirection();
    m_player.snakeRender(&window);

    window.display();
  }

  return 0;
}
