#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

class Map {
public:
  Map(char *map_path, char *apple_path);

  void drawMap(sf::RenderWindow *window);

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
