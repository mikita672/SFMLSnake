#include "snake.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <iostream>
#define SNAKE_SPEED 0.3f

Snake::Snake(std::string path) {
  snakeHeadImg.loadFromFile(path + "/Head_snake_4pos32.png");
  snakeBodyImg.loadFromFile(path + "/Body_snake_4pos32.png");
  snakeTailImg.loadFromFile(path + "/Tail_snake_4pos32.png");
  snakeLinkImg.loadFromFile(path + "/Link_snake_4pos32.png");

  snakeHeadTexture.loadFromImage(snakeHeadImg);
  snakeBodyTexture.loadFromImage(snakeBodyImg);
  snakeTailTexture.loadFromImage(snakeTailImg);
  snakeLinkTexture.loadFromImage(snakeLinkImg);

  snakeHeadSprite.setTexture(snakeHeadTexture);
  snakeBodySprite.setTexture(snakeBodyTexture);
  snakeTailSprite.setTexture(snakeTailTexture);
  snakeLinkSprite.setTexture(snakeLinkTexture);

  snakeBody.push_back(snakeTile(5, 5, UP)); // head
  snakeBody.push_back(snakeTile(5, 6, UP)); // body
  snakeBody.push_back(snakeTile(5, 7, UP)); // tail
  gameRunning = false;
}

void Snake::updateSnakeDirection() {
  prevDir = snakeDirection;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {

    snakeDirection = LEFT;
    gameRunning = true;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
    snakeDirection = RIGHT;
    gameRunning = true;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
    snakeDirection = UP;
    gameRunning = true;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
    snakeDirection = DOWN;
    gameRunning = true;
  }
  if (prevDir != snakeDirection && prevDir != STOPED) {
    posChanged = true;
  } else {
    posChanged = false;
  }
}

void Snake::snakeMovement(sf::Clock *clock) {
  if (clock->getElapsedTime().asSeconds() >= SNAKE_SPEED && gameRunning) {

    sf::Vector2i newHead(snakeBody[0].getPosition().x,
                         snakeBody[0].getPosition().y);

    if (snakeDirection == UP) {
      newHead.y -= 1;
    } else if (snakeDirection == DOWN) {
      newHead.y += 1;
    } else if (snakeDirection == RIGHT) {
      newHead.x += 1;
    } else if (snakeDirection == LEFT) {
      newHead.x -= 1;
    }
    if (newHead.y < 0) {
      newHead.y = 15;
    }
    if (newHead.x < 0) {
      newHead.x = 15;
    }
    if (newHead.y > 15) {
      newHead.y = 0;
    }
    if (newHead.x > 15) {
      newHead.x = 0;
    }

    snakeBody.insert(snakeBody.begin(),
                     snakeTile(newHead.x, newHead.y, snakeDirection));

    snakeBody.pop_back();

    clock->restart();
  }
}
void Snake::snakeRender(sf::RenderWindow *window, sf::Clock *clock) {
  snakeHeadSprite.setPosition(snakeBody[0].getPosition().x * 32,
                              snakeBody[0].getPosition().y * 32);
  if (snakeBody[0].getDirection() == DOWN) {
    snakeHeadSprite.setTextureRect(sf::Rect(0, 96, 32, 32));
  } else if (snakeBody[0].getDirection() == RIGHT) {
    snakeHeadSprite.setTextureRect(sf::Rect(0, 32, 32, 32));
  } else if (snakeBody[0].getDirection() == UP) {
    snakeHeadSprite.setTextureRect(sf::Rect(0, 0, 32, 32));
  } else if (snakeBody[0].getDirection() == LEFT) {
    snakeHeadSprite.setTextureRect(sf::Rect(0, 64, 32, 32));
  }
  window->draw(snakeHeadSprite);

  for (size_t i = 1; i < snakeBody.size() - 1; i++) {

    if ((snakeBody[i - 1].getDirection() == RIGHT &&
         snakeBody[i + 1].getDirection() == UP) ||
        (snakeBody[i - 1].getDirection() == DOWN &&
         snakeBody[i + 1].getDirection() == LEFT)) {
      snakeLinkSprite.setPosition(snakeBody[i].getPosition().x * 32,
                                  snakeBody[i].getPosition().y * 32);
      snakeLinkSprite.setTextureRect(sf::Rect(0, 32, 32, 32));
      window->draw(snakeLinkSprite);
    } else if ((snakeBody[i - 1].getDirection() == LEFT &&
                snakeBody[i + 1].getDirection() == UP) ||
               (snakeBody[i - 1].getDirection() == DOWN &&
                snakeBody[i + 1].getDirection() == RIGHT)) {
      snakeLinkSprite.setPosition(snakeBody[i].getPosition().x * 32,
                                  snakeBody[i].getPosition().y * 32);
      snakeLinkSprite.setTextureRect(sf::Rect(0, 64, 32, 32));
      window->draw(snakeLinkSprite);
    } else if ((snakeBody[i + 1].getDirection() == LEFT &&
                snakeBody[i - 1].getDirection() == UP) ||
               (snakeBody[i + 1].getDirection() == DOWN &&
                snakeBody[i - 1].getDirection() == RIGHT)) {
      snakeLinkSprite.setPosition(snakeBody[i].getPosition().x * 32,
                                  snakeBody[i].getPosition().y * 32);
      snakeLinkSprite.setTextureRect(sf::Rect(0, 0, 32, 32));
      window->draw(snakeLinkSprite);
    } else if ((snakeBody[i + 1].getDirection() == RIGHT &&
                snakeBody[i - 1].getDirection() == UP) ||
               (snakeBody[i + 1].getDirection() == DOWN &&
                snakeBody[i - 1].getDirection() == LEFT)) {
      snakeLinkSprite.setPosition(snakeBody[i].getPosition().x * 32,
                                  snakeBody[i].getPosition().y * 32);
      snakeLinkSprite.setTextureRect(sf::Rect(0, 96, 32, 32));
      window->draw(snakeLinkSprite);

    } else {

      snakeBodySprite.setPosition(snakeBody[i].getPosition().x * 32,
                                  snakeBody[i].getPosition().y * 32);

      if (snakeBody[i].getDirection() == DOWN) {
        snakeBodySprite.setTextureRect(sf::Rect(0, 96, 32, 32));
      } else if (snakeBody[i].getDirection() == RIGHT) {
        snakeBodySprite.setTextureRect(sf::Rect(0, 32, 32, 32));
      } else if (snakeBody[i].getDirection() == UP) {
        snakeBodySprite.setTextureRect(sf::Rect(0, 0, 32, 32));
      } else if (snakeBody[i].getDirection() == LEFT) {
        snakeBodySprite.setTextureRect(sf::Rect(0, 64, 32, 32));
      }

      window->draw(snakeBodySprite);
    }

    snakeTailSprite.setPosition(snakeBody.back().getPosition().x * 32,
                                snakeBody.back().getPosition().y * 32);
    if (snakeBody.back().getDirection() == DOWN) {
      snakeTailSprite.setTextureRect(sf::Rect(0, 96, 32, 32));
    } else if (snakeBody.back().getDirection() == RIGHT) {
      snakeTailSprite.setTextureRect(sf::Rect(0, 32, 32, 32));
    } else if (snakeBody.back().getDirection() == UP) {
      snakeTailSprite.setTextureRect(sf::Rect(0, 0, 32, 32));
    } else if (snakeBody.back().getDirection() == LEFT) {
      snakeTailSprite.setTextureRect(sf::Rect(0, 64, 32, 32));
    }
    snakeTailSprite.setOrigin(0, 0);
    window->draw(snakeTailSprite);
    snakeBody.back().setDirection(
        snakeBody[snakeBody.size() - 2].getDirection());
  }
}

sf::Vector2i Snake::getHeadPos() {
  return sf::Vector2i(snakeBody[0].getPosition());
}

std::vector<snakeTile> Snake::getEntireSnakePos() { return this->snakeBody; }
