#include <SFML/Graphics.hpp>
#include <iostream>
#include "snake.h"

#define SNAKE_SPEED 0.3f

Snake::Snake(std::string path) : snakeHeadSprite(snakeHeadTexture), snakeBodySprite(snakeBodyTexture), snakeTailSprite(snakeTailTexture), snakeLinkSprite(snakeLinkTexture) {
	snakeHeadImg.loadFromFile(path + "/Head_snake_4pos32.png");
	snakeBodyImg.loadFromFile(path + "/Body_snake_4pos32.png");
	snakeTailImg.loadFromFile(path + "/Tail_snake_4pos32.png");
	snakeLinkImg.loadFromFile(path + "/Link_snake_4pos32.png");

	snakeHeadTexture.loadFromImage(snakeHeadImg);
	snakeBodyTexture.loadFromImage(snakeBodyImg);
	snakeTailTexture.loadFromImage(snakeTailImg);
	snakeLinkTexture.loadFromImage(snakeLinkImg);


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
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		snakeDirection = RIGHT;
		gameRunning = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
		snakeDirection = UP;
		gameRunning = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
		snakeDirection = DOWN;
		gameRunning = true;
	}
	if (prevDir != snakeDirection && prevDir != STOPED) {
		posChanged = true;
	}
	else {
		posChanged = false;
	}
}

void Snake::snakeMovement(sf::Clock* clock) {
	if (clock->getElapsedTime().asSeconds() >= SNAKE_SPEED && gameRunning) {

		sf::Vector2i newHead(snakeBody[0].getPosition().x,
			snakeBody[0].getPosition().y);

		if (snakeDirection == UP) {
			newHead.y -= 1;
		}
		else if (snakeDirection == DOWN) {
			newHead.y += 1;
		}
		else if (snakeDirection == RIGHT) {
			newHead.x += 1;
		}
		else if (snakeDirection == LEFT) {
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
		if (!this->increase) {
			snakeBody.pop_back();
		}
		else {
			this->increase = false;
		}

		for (size_t i = 1; i < snakeBody.size(); i++) {
			sf::Vector2i prevPos = snakeBody[i - 1].getPosition();
			sf::Vector2i currentPos = snakeBody[i].getPosition();

			int dx = prevPos.x - currentPos.x;
			int dy = prevPos.y - currentPos.y;

			if (dx > 1) dx = -1;
			else if (dx < -1) dx = 1;
			if (dy > 1) dy = -1;
			else if (dy < -1) dy = 1;

			if (dx == 1) snakeBody[i].setDirection(RIGHT);
			else if (dx == -1) snakeBody[i].setDirection(LEFT);
			else if (dy == 1) snakeBody[i].setDirection(DOWN);
			else if (dy == -1) snakeBody[i].setDirection(UP);
		}

		snakeBody[0].setDirection(snakeDirection);

		clock->restart();
	}
}
void Snake::snakeRender(sf::RenderWindow* window, sf::Clock* clock) {
	snakeHeadSprite.setPosition(sf::Vector2f(snakeBody[0].getPosition().x * 32,
		snakeBody[0].getPosition().y * 32));
	if (snakeBody[0].getDirection() == DOWN) {
		snakeHeadSprite.setTextureRect(sf::Rect(sf::Vector2i(0, 96), sf::Vector2i(32, 32)));
	}
	else if (snakeBody[0].getDirection() == RIGHT) {
		snakeHeadSprite.setTextureRect(sf::Rect(sf::Vector2i(0, 32), sf::Vector2i(32, 32)));
	}
	else if (snakeBody[0].getDirection() == UP) {
		snakeHeadSprite.setTextureRect(sf::Rect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)));
	}
	else if (snakeBody[0].getDirection() == LEFT) {
		snakeHeadSprite.setTextureRect(sf::Rect(sf::Vector2i(0, 64), sf::Vector2i(32, 32)));
	}
	window->draw(snakeHeadSprite);

	for (size_t i = 1; i < snakeBody.size() - 1; i++) {
		sf::Vector2i prevPos = snakeBody[i - 1].getPosition();
		sf::Vector2i currentPos = snakeBody[i].getPosition();
		sf::Vector2i nextPos = snakeBody[i + 1].getPosition();

		int dx_prev = prevPos.x - currentPos.x;
		int dy_prev = prevPos.y - currentPos.y;
		int dx_next = nextPos.x - currentPos.x;
		int dy_next = nextPos.y - currentPos.y;

		if (dx_prev > 1) dx_prev = -1; else if (dx_prev < -1) dx_prev = 1;
		if (dy_prev > 1) dy_prev = -1; else if (dy_prev < -1) dy_prev = 1;
		if (dx_next > 1) dx_next = -1; else if (dx_next < -1) dx_next = 1;
		if (dy_next > 1) dy_next = -1; else if (dy_next < -1) dy_next = 1;

		bool isCorner = (dx_prev * dy_next != dy_prev * dx_next);

		if (isCorner) {
			snakeLinkSprite.setPosition(sf::Vector2f(
				snakeBody[i].getPosition().x * 32,
				snakeBody[i].getPosition().y * 32
			));

			if ((dx_prev == 1 && dy_next == -1) || (dy_prev == -1 && dx_next == 1)) {
				snakeLinkSprite.setTextureRect(sf::Rect(sf::Vector2i(0, 0), sf::Vector2i(32, 32))); // left -> up || down -> right
			}
			else if ((dx_prev == 1 && dy_next == 1) || (dy_prev == 1 && dx_next == 1)) {
				snakeLinkSprite.setTextureRect(sf::Rect(sf::Vector2i(0, 32), sf::Vector2i(32, 32)));  // left -> down, up -> right
			}
			else if ((dx_prev == -1 && dy_next == 1) || (dy_prev == 1 && dx_next == -1)) {  // right -> down, up -> left
				snakeLinkSprite.setTextureRect(sf::Rect(sf::Vector2i(0, 64), sf::Vector2i(32, 32)));
			}
			else
				if ((dx_prev == -1 && dy_next == -1) || (dy_prev == -1 && dx_next == -1)) {  // right -> up, down -> left
					snakeLinkSprite.setTextureRect(sf::Rect(sf::Vector2i(0, 96), sf::Vector2i(32, 32)));
				}

			window->draw(snakeLinkSprite);
		}
		else {
			snakeBodySprite.setPosition(sf::Vector2f(
				snakeBody[i].getPosition().x * 32,
				snakeBody[i].getPosition().y * 32
			));

			if (dx_prev == 0) {
				snakeBodySprite.setTextureRect(sf::Rect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)));
			}
			else {
				snakeBodySprite.setTextureRect(sf::Rect(sf::Vector2i(0, 32), sf::Vector2i(32, 32)));
			}

			window->draw(snakeBodySprite);
		}
	}

	if (snakeBody.size() > 1) {
		snakeTailSprite.setPosition(sf::Vector2f(snakeBody.back().getPosition().x * 32,
			snakeBody.back().getPosition().y * 32));
		if (snakeBody.back().getDirection() == DOWN) {
			snakeTailSprite.setTextureRect(sf::Rect(sf::Vector2i(0, 96), sf::Vector2i(32, 32)));
		}
		else if (snakeBody.back().getDirection() == RIGHT) {
			snakeTailSprite.setTextureRect(sf::Rect(sf::Vector2i(0, 32), sf::Vector2i(32, 32)));
		}
		else if (snakeBody.back().getDirection() == UP) {
			snakeTailSprite.setTextureRect(sf::Rect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)));
		}
		else if (snakeBody.back().getDirection() == LEFT) {
			snakeTailSprite.setTextureRect(sf::Rect(sf::Vector2i(0, 64), sf::Vector2i(32, 32)));
		}
		window->draw(snakeTailSprite);

	}
}

sf::Vector2i Snake::getHeadPos() {
	return sf::Vector2i(snakeBody[0].getPosition());
}

std::vector<snakeTile> Snake::getEntireSnakePos() { return this->snakeBody; }

void Snake::increaseSize() { this->increase = true; }