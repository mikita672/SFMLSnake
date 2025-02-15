#ifndef MAP_H
#define MAP_H

#include "snake.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Map {
public:
  Map(std::string map_path, std::string apple_path);
  void drawMap(sf::RenderWindow *window);
  sf::Vector2i getApplePos();
  void run(sf::Clock *clock, sf::RenderWindow *window, Snake *player);
  void checkAppleColission(Snake *player);
  void renderApple(sf::RenderWindow *window, std::vector<snakeTile> snake);

private:
  sf::Image mapImage;
  sf::Texture mapTexture;
  sf::Sprite mapSprite;

  sf::Image appleImage;
  sf::Texture appleTexture;
  sf::Sprite appleSprite;
  int apple_posX, apple_posY;
};
#endif // !MAP_H
