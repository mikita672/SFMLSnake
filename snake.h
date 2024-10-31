#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>

enum direction { LEFT, RIGHT, UP, DOWN, STOPED };

class Snake {
private:
  int posX = 8;
  int posY = 11;
  sf::Image snakeImg;
  sf::Texture snakeTexture;
  direction snakeDirection = STOPED;

  sf::Sprite snakeHeadSprite;
  sf::Sprite snakeBodySprite;
  sf::Sprite snakeTailSprite;

public:
  Snake(char *path);
  void updateSnakeDirection();

  void snakeMovement(sf::Clock *clock);

  void snakeRender(sf::RenderWindow *window);
};

#endif
