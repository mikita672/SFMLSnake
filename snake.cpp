#include "snake.h"

Snake::Snake(char *path) {

  snakeImg.loadFromFile(path);
  snakeTexture.loadFromImage(snakeImg);
  snakeHeadSprite.setTexture(snakeTexture);
  snakeHeadSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
  snakeBodySprite.setTexture(snakeTexture);
  snakeBodySprite.setTextureRect(sf::IntRect(0, 32, 32, 32));
  snakeTailSprite.setTexture(snakeTexture);
  snakeTailSprite.setTextureRect(sf::IntRect(0, 64, 32, 32));
}

void Snake::updateSnakeDirection() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
    snakeDirection = LEFT;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
    snakeDirection = RIGHT;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
    snakeDirection = UP;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
    snakeDirection = DOWN;
  }
}

void Snake::snakeMovement(sf::Clock *clock) {
  if (clock->getElapsedTime().asSeconds() >= 0.3f) {
    if (snakeDirection == UP) {
      posY -= 1;
    } else if (snakeDirection == DOWN) {
      posY += 1;
    } else if (snakeDirection == RIGHT) {
      posX += 1;
    } else if (snakeDirection == LEFT) {
      posX -= 1;
    }
    if (posY < 0) {
      posY = 13;
    }
    if (posX < 0) {
      posX = 13;
    }
    if (posY > 13) {
      posY = 0;
    }
    if (posX > 13) {
      posX = 0;
    }
    clock->restart();
  }
}

void Snake::snakeRender(sf::RenderWindow *window) {
  if (snakeDirection == STOPED || snakeDirection == UP) {
    snakeBodySprite.setRotation(0);
    snakeTailSprite.setRotation(0);
    snakeHeadSprite.setRotation(0);
    snakeHeadSprite.setPosition(posX * 32, (posY) * 32);
    snakeBodySprite.setPosition(posX * 32, (posY + 1) * 32);
    snakeTailSprite.setPosition(posX * 32, (posY + 2) * 32);
  } else if (snakeDirection == DOWN) {
    snakeHeadSprite.setPosition(posX * 32, (posY) * 32);
    snakeBodySprite.setPosition(posX * 32, (posY - 1) * 32);
    snakeTailSprite.setPosition(posX * 32, (posY - 2) * 32);
    snakeHeadSprite.setRotation(180);
    snakeBodySprite.setRotation(180);
    snakeTailSprite.setRotation(180);
  } else if (snakeDirection == LEFT) {
    snakeHeadSprite.setPosition(posX * 32, posY * 32);
    snakeBodySprite.setPosition((posX + 1) * 32, posY * 32);
    snakeTailSprite.setPosition((posX + 2) * 32, posY * 32);
    snakeHeadSprite.setRotation(270);
    snakeBodySprite.setRotation(270);
    snakeTailSprite.setRotation(270);
  } else if (snakeDirection == RIGHT) {
    snakeHeadSprite.setPosition(posX * 32, posY * 32);
    snakeBodySprite.setPosition((posX - 1) * 32, posY * 32);
    snakeTailSprite.setPosition((posX - 2) * 32, posY * 32);
    snakeHeadSprite.setRotation(90);
    snakeBodySprite.setRotation(90);
    snakeTailSprite.setRotation(90);
  }

  window->draw(snakeHeadSprite);
  window->draw(snakeBodySprite);
  window->draw(snakeTailSprite);
}
