#include <iostream>
#include <SFML/Graphics/Rect.hpp>
#include "map.h"
#include "snake.h"

Map::Map(std::string map_path, std::string apple_path)
    : mapSprite(mapTexture),
    appleSprite(appleTexture)
{
    if (!mapImage.loadFromFile(map_path)) {
        std::cerr << "Failed to load map image!" << std::endl;
    }
    mapTexture.loadFromImage(mapImage);

    if (!appleImage.loadFromFile(apple_path)) {
        std::cerr << "Failed to load apple image!" << std::endl;
    }
    appleTexture.loadFromImage(appleImage);
    appleSprite.setTextureRect(sf::Rect(sf::Vector2i(0, 64), sf::Vector2i(32, 32)));

    apple_posX = rand() % 16;
    apple_posY = rand() % 16;
}

void Map::drawMap(sf::RenderWindow* window) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (i % 2 == 0) {
                if (j % 2 == 0) {
                    mapSprite.setTextureRect(sf::Rect(sf::Vector2i(0, 0),sf::Vector2i(32, 32)));
                }
                else {
                    mapSprite.setTextureRect(sf::Rect(sf::Vector2i(0, 32), sf::Vector2i(32, 32)));
                }
            }
            else {
                if (j % 2 == 0) {
                    mapSprite.setTextureRect(sf::Rect(sf::Vector2i(0, 32), sf::Vector2i(32, 32)));
                }
                else {
                    mapSprite.setTextureRect(sf::Rect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)));
                }
            }
            mapSprite.setPosition(sf::Vector2f((float)j * 32, (float)i * 32));
            window->draw(mapSprite);
        }
    }
}

void Map::checkAppleColission(Snake* player) {
    if (this->getApplePos() == player->getHeadPos()) {
        apple_posX = rand() % 16;
        apple_posY = rand() % 16;
        player->increaseSize();
    }
}

sf::Vector2i Map::getApplePos() { return sf::Vector2i(apple_posX, apple_posY); }

void Map::run(sf::Clock* clock, sf::RenderWindow* window, Snake* player) {
    this->checkAppleColission(player);
    this->renderApple(window, player->getEntireSnakePos());
    player->snakeMovement(clock);
    player->updateSnakeDirection();
    player->snakeRender(window, clock);
    if (player->checkCollision()) {
        player->changeGameState();
    }
}

void Map::renderApple(sf::RenderWindow* window, std::vector<snakeTile> snake) {
    while (true) {
        appleSprite.setPosition(sf::Vector2f((float)apple_posX * 32, (float)apple_posY * 32));
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