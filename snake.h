#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>

enum direction { LEFT, RIGHT, UP, DOWN, STOPED };

class snakeTile {
private:
  sf::Vector2i position;
  enum direction spriteDirection;

public:
  snakeTile(int x, int y, enum direction dir) {
    this->position = sf::Vector2i(x, y);
    this->spriteDirection = dir;
  }

  void setPosition(sf::Vector2i pos) { position = pos; }
  void setDirection(enum direction dir) { spriteDirection = dir; }
  sf::Vector2i getPosition() { return this->position; }
  enum direction getDirection() { return this->spriteDirection; }
  void setParameters(sf::Vector2i pos, enum direction dir) {
    this->spriteDirection = dir;
    this->position = pos;
  }
};

class Snake {
private:
  sf::Image snakeHeadImg;
  sf::Image snakeBodyImg;
  sf::Image snakeTailImg;
  sf::Image snakeLinkImg;
  sf::Texture snakeHeadTexture;
  sf::Texture snakeBodyTexture;
  sf::Texture snakeTailTexture;
  sf::Texture snakeLinkTexture;
  direction snakeDirection = STOPED;

  sf::Sprite snakeHeadSprite;
  sf::Sprite snakeBodySprite;
  sf::Sprite snakeTailSprite;
  sf::Sprite snakeLinkSprite;

  std::vector<snakeTile> snakeBody;
  bool gameRunning;

  direction prevDir;
  bool posChanged = false;

public:
  Snake(std::string path);
  void updateSnakeDirection();
  void snakeMovement(sf::Clock *clock);
  void snakeRender(sf::RenderWindow *window, sf::Clock *clock);
  sf::Vector2i getHeadPos();
  std::vector<snakeTile> getEntireSnakePos();
};

#endif
