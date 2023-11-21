#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>
#include "Projectile.h"
#include "Vector.h"
#include "AddOn.h"

using namespace sf;
class Player
#include <cmath>
{
public:
	Texture shipSheet, bulletTexture, rotatedBullets[6];
	int shipWidth, shipHeight;
	Sprite sprite;
	float speed = 0.1;
	bool fire;
	int x, y;
	int m_angle;
	float rotateDelay, fireDelay, fireTimer, dropTimer;
	bool canMoveVert, canMoveHoriz;

	bool moveRight, moveLeft, moveTop, moveDown;

	bool fireAddon;
	bool powerUpAddon;
	float powerUpTimer, fireAddonTimer;

	bool blinking;
	float blinkTimer, blinkTrack;
	bool blink;
	int blinks;

	int m_lives;
	bool breaking;
	int m_score;

	Text m_scoreText;
	Font m_scoreFont;

	AddOn* drop;

	Vector<Bullet> bullets;

	Player(std::string png_path)
	{
		shipSheet.loadFromFile(png_path);
		bulletTexture.loadFromFile("img/bullet0.png");
		rotatedBullets[0].loadFromFile("img/bulletm30.png");
		rotatedBullets[1].loadFromFile("img/bulletm20.png");
		rotatedBullets[2].loadFromFile("img/bulletm10.png");
		rotatedBullets[3].loadFromFile("img/bullet10.png");
		rotatedBullets[4].loadFromFile("img/bullet20.png");
		rotatedBullets[5].loadFromFile("img/bullet30.png");

		sprite.setTexture(shipSheet);
		x = 683;
		y = 660;
		sprite.setPosition(x, y);
		fire = false;
		m_angle = 90;
		shipWidth = shipSheet.getSize().x / 19;
		shipHeight = shipSheet.getSize().y / 19;
		int topLeft = m_angle % 19;
		int top = m_angle / 19;
		sprite.setTextureRect(sf::IntRect(topLeft * shipWidth, top * shipHeight, shipWidth, shipHeight));
		fireDelay = 0.6;
		fireTimer = 0;
		dropTimer = 0;
		rotateDelay = 0.05;
		canMoveVert = true;
		canMoveHoriz = true;

		fireAddonTimer = 0;
		powerUpTimer = 0;

		fireAddon = false;
		powerUpAddon = false;
		
		blinking = false;
		blink = false;

		moveRight = false;
		moveLeft = false;
		moveTop = false;
		moveDown = false;

		blinkTimer = 0;
		blinkTrack = 0;
		blinks = 0;

		m_scoreFont.loadFromFile("fonts/comicsans.ttf");
		m_scoreText.setFont(m_scoreFont);
		m_scoreText.setCharacterSize(25);

		m_lives = 3;
		breaking = false;
		m_score = 0;

		drop = nullptr;
	}
	void fireBullet()
	{
		if (fire) {
			if (fireTimer < fireDelay) {
				fire = false;
				return;
			}
			if (powerUpAddon) {
				bullets.push_back(Bullet(rotatedBullets[0], vector2f(sprite.getPosition().x + 40, sprite.getPosition().y), 120));
				bullets.push_back(Bullet(rotatedBullets[1], vector2f(sprite.getPosition().x + 40, sprite.getPosition().y), 110));
				bullets.push_back(Bullet(rotatedBullets[2], vector2f(sprite.getPosition().x + 40, sprite.getPosition().y), 100));
				bullets.push_back(Bullet(rotatedBullets[3], vector2f(sprite.getPosition().x + 40, sprite.getPosition().y), 80));
				bullets.push_back(Bullet(rotatedBullets[4], vector2f(sprite.getPosition().x + 40, sprite.getPosition().y), 70));
				bullets.push_back(Bullet(rotatedBullets[5], vector2f(sprite.getPosition().x + 40, sprite.getPosition().y), 60));
			}
			bullets.push_back(Bullet(bulletTexture, vector2f(sprite.getPosition().x + 40, sprite.getPosition().y)));
			fire = false;
			fireTimer = 0;
		}
	}
	void controlBullet(sf::Time& dT) {
		for (int i = 0; i < bullets.size(); ++i) {
			bullets[i].updateProjectile(dT);
			if (bullets[i].leftScreen())
				bullets.erase(i);
		}
	}

	void move(std::string s, sf::Time& dt) {
		float delta_x = 0, delta_y = 0;

		if (moveTop && moveLeft) {
			m_angle = 135;
			int topLeft = m_angle % 19;
			int top = m_angle / 19;
			sprite.setTextureRect(sf::IntRect(topLeft * shipWidth, top * shipHeight, shipWidth, shipHeight));
		}
		else if (moveTop && moveRight) {
			m_angle = 45;
			int topLeft = m_angle % 19;
			int top = m_angle / 19;
			sprite.setTextureRect(sf::IntRect(topLeft * shipWidth, top * shipHeight, shipWidth, shipHeight));
		}
		else if (moveDown && moveLeft) {
			m_angle = 225;
			int topLeft = m_angle % 19;
			int top = m_angle / 19;
			sprite.setTextureRect(sf::IntRect(topLeft * shipWidth, top * shipHeight, shipWidth, shipHeight));
		}
		else if (moveDown && moveRight) {
			m_angle = 315;
			int topLeft = m_angle % 19;
			int top = m_angle / 19;
			sprite.setTextureRect(sf::IntRect(topLeft * shipWidth, top * shipHeight, shipWidth, shipHeight));
		}
		else {
			m_angle = 90;
			int topLeft = m_angle % 19;
			int top = m_angle / 19;
			sprite.setTextureRect(sf::IntRect(topLeft * shipWidth, top * shipHeight, shipWidth, shipHeight));
		}

		if (s == "l")
			delta_x = -1;
		else if (s == "r")
			delta_x = 1;
		else if (s == "u")
			delta_y = -1;
		else if (s == "d")
			delta_y = 1;
		if (canMoveVert == false)
			delta_y = 0;
		if (canMoveHoriz == false)
			delta_x = 0;



		delta_y *= speed;
		delta_x *= speed;

		

		sprite.move(delta_x * dt.asSeconds() * 5000, delta_y * dt.asSeconds() * 5000);
	}

	void wrapAround() {
		if (sprite.getPosition().y <= -110)
			sprite.setPosition(sprite.getPosition().x, 768);
		else if (sprite.getPosition().y >= 768)
			sprite.setPosition(sprite.getPosition().x, -110);
		else if (sprite.getPosition().x <= -110)
			sprite.setPosition(1366, sprite.getPosition().y);
		else if (sprite.getPosition().x > 1366)
			sprite.setPosition(-110, sprite.getPosition().y);
	}

	void dropAddons(Texture* addonTex) {
		if (dropTimer >= 10) {
			dropTimer = 0;

			int n = rand() % 4;
			if (n == 0) {
				drop = new Danger(addonTex[0]);
				drop->setPos((rand() % 14) * 100, -100);
				drop->getSprite().setScale(0.65, 0.65);
			}
			else if (n == 1) {
				drop = new PowerUp(addonTex[1]);
				drop->setPos((rand() % 14) * 100, -100);
				drop->getSprite().setScale(0.65, 0.65);
			}
			else if (n == 2) {
				drop = new Fire(addonTex[2]);
				drop->setPos((rand() % 14) * 100, -100);
				drop->getSprite().setScale(0.65, 0.65);
			}
			else {
				drop = new Life(addonTex[3]);
				drop->setPos((rand() % 14) * 100, -100);
				drop->getSprite().setScale(0.65, 0.65);
			}

		}
	}

	void moveDrops(Vector<AddOn*>& drops, sf::Time& dT) {
		if (drop != nullptr) {
			drop->move(0, 0.05 * dT.asSeconds() * 5000);

			if ((sprite.getPosition().x + sprite.getTextureRect().width >= drop->getPos().x
				&& sprite.getPosition().y + sprite.getTextureRect().height >= drop->getPos().y
				&& (sprite.getPosition().x <= drop->getSprite().getGlobalBounds().left + drop->getSprite().getGlobalBounds().width
					&& sprite.getPosition().y <= drop->getSprite().getGlobalBounds().top + drop->getSprite().getGlobalBounds().height))) {

				if (drop->addonType() == 1) {
					if (canDie()) {
						reduceLife();
						delete drop;
						drop = nullptr;
					}
				}
				else if (drop->addonType() == 2) {
					powerUpAddon = true;
					if (blinking) {
						blinkTimer = 0;
						blinks = 0;
						blinking = false;
						blink = false;
						blinkTrack = 0;
					}
					delete drop;
					drop = nullptr;
				}
				else if (drop->addonType() == 3) {
					fireAddon = true;
					delete drop;
					drop = nullptr;
				}
				else if (drop->addonType() == 4) {
					if (m_lives < 3)
						++m_lives;
					delete drop;
					drop = nullptr;
				}
			}

			else if (drop->getPos().y >= 768) {
				if (drop->addonType() == 1) {
					m_score += 30;
				}
				delete drop;
				drop = nullptr;
			}
		}
	}

	void drawDrop(sf::RenderWindow& window) {
		window.draw(drop->getSprite());
	}

	void timeAddons() {
		if (fireAddonTimer >= 5) {
			fireAddonTimer = 0;
			fireAddon = false;
		}
		if (powerUpTimer >= 5) {
			powerUpTimer = 0;
			powerUpAddon = false;
		}
	}

	void drawSprite(sf::RenderWindow& window, float time) {
		if (blinking) {
			blinkTimer += time;
			blinkTrack += time;
			if (blinkTrack >= 0.2 - (0.01 * blinks)) {
				++blinks;
				if (blink == false)
					blink = true;
				else if (blink == true)
					blink = false;
				blinkTrack = 0;
			}
			if (blink == false)
				return;
			else if (blink == true)
				window.draw(sprite);
			if (blinkTimer >= 3) {
				blinkTimer = 0;
				blinks = 0;
				blinking = false;
				blink = false;
				blinkTrack = 0;
			}
		}
		else
			window.draw(sprite);
	}

	void drawScore(sf::RenderWindow& window) {
		m_scoreText.setString("* score " + std::to_string(m_score));
		m_scoreText.setPosition(90, 710);
		window.draw(m_scoreText);
	}

	void reduceLife() {
		if (blinking == false && powerUpAddon == false) {
			blinking = true;
			breaking = true;
			m_lives -= 1;
		}
	}

	bool canDie() const { return (blinking == false && powerUpAddon == false); }

	void incScore(int n) { m_score += n; }
};
