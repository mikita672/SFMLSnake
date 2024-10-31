#include "snake.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>

void drawMap(sf::RenderWindow *window, sf::Sprite *mapSprite,
             sf::Sprite *appleSprite, int apple_posX, int apple_posY) {
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      if (i % 2 == 0) {
        if (j % 2 == 0) {
          mapSprite->setTextureRect(sf::IntRect(0, 0, 32, 32));
        } else {
          mapSprite->setTextureRect(sf::IntRect(0, 32, 32, 32));
        }
      } else {
        if (j % 2 == 0) {
          mapSprite->setTextureRect(sf::IntRect(0, 32, 32, 32));
        } else {
          mapSprite->setTextureRect(sf::IntRect(0, 0, 32, 32));
        }
      }
      mapSprite->setPosition((float)j * 32, (float)i * 32);
      window->draw(*mapSprite);
      if (i == apple_posX && j == apple_posY) {
        appleSprite->setPosition((float)j * 32, (float)i * 32);
        window->draw(*appleSprite);
      }
    }
  }
}

int main() {
  std::srand(time(NULL));

  sf::Clock clock;

  Snake m_player("Resources/Sprites/Snake/Full_snake32.png");

  sf::Image mapImage;
  mapImage.loadFromFile("Resources/Sprites/Map/Full_map_32.png");
  sf::Texture mapTexture;
  mapTexture.loadFromImage(mapImage);
  sf::Sprite mapSprite;
  mapSprite.setTexture(mapTexture);

  sf::Image appleImage;
  appleImage.loadFromFile("Resources/Sprites/Map/Full_map_32.png");
  sf::Texture appleTexture;
  appleTexture.loadFromImage(appleImage);
  sf::Sprite appleSprite;
  appleSprite.setTexture(appleTexture);
  appleSprite.setTextureRect(sf::IntRect(0, 64, 32, 32));
  int apple_posX = rand() % 16;
  int apple_posY = rand() % 16;

  sf::RenderWindow window(sf::VideoMode(512, 512), "SNAKE!");
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();

    drawMap(&window, &mapSprite, &appleSprite, apple_posX, apple_posY);
    m_player.snakeMovement(&clock);
    m_player.updateSnakeDirection();
    m_player.snakeRender(&window);

    window.display();
  }

  return 0;
}
