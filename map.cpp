#include "map.h"

Map::Map(char *map_path, char *apple_path) {
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
      if (i == apple_posX && j == apple_posY) {
        appleSprite.setPosition((float)j * 32, (float)i * 32);
        window->draw(appleSprite);
      }
    }
  }
}
