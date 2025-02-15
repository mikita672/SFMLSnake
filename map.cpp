#include "map.h"
#include "snake.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>

Map::Map(std::string map_path, std::string apple_path) {
  mapImage.loadFromFile(map_path);
  mapTexture.loadFromImage(mapImage);
  mapSprite.setTexture(mapTexture);

  appleImage.loadFromFile(apple_path);
  appleTexture.loadFromImage(appleImage);
  appleSprite.setTexture(appleTexture);
  appleSprite.setTextureRect(sf::IntRect(0, 64, 32, 32));
  apple_posX = rand() % 16;
  apple_posY = rand() % 16;
}

void Map::drawMap(sf::RenderWindow *window) {
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      if (i % 2 == 0) {
        if (j % 2 == 0) {
          mapSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
        } else {
          mapSprite.setTextureRect(sf::IntRect(0, 32, 32, 32));
        }
      } else {
        if (j % 2 == 0) {
          mapSprite.setTextureRect(sf::IntRect(0, 32, 32, 32));
        } else {
          mapSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
        }
      }
      mapSprite.setPosition((float)j * 32, (float)i * 32);
      window->draw(mapSprite);
    }
  }
}

void Map::checkAppleColission(Snake *player) {
  if (this->getApplePos() == player->getHeadPos()) {
    apple_posX = rand() % 16;
    apple_posY = rand() % 16;
  }
}

sf::Vector2i Map::getApplePos() { return sf::Vector2i(apple_posX, apple_posY); }

void Map::run(sf::Clock *clock, sf::RenderWindow *window, Snake *player) {
  this->checkAppleColission(player);
  std::cout << "Apple pos: (" << this->getApplePos().x << ", "
            << this->getApplePos().y << "), Snake pos: ("
            << player->getHeadPos().x << ", " << player->getHeadPos().y << ")"
            << std::endl;
  this->renderApple(window, player->getEntireSnakePos());
  player->snakeMovement(clock);
  player->updateSnakeDirection();
  player->snakeRender(window, clock);
}

void Map::renderApple(sf::RenderWindow *window, std::vector<snakeTile> snake) {
  while (true) {
    appleSprite.setPosition((float)apple_posX * 32, (float)apple_posY * 32);
    for (size_t i = 0; i < snake.size(); i++) {
      if (apple_posX == snake[i].getPosition().x &&
          apple_posY == snake[i].getPosition().y) {
        continue;
      }
    }
    break;
  }
  window->draw(appleSprite);
}
