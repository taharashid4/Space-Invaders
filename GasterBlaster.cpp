#include "GasterBlaster.h"
#include "vector2f.h"

void blasterMove(vector2f point, sf::Sprite& sprite, float spd, sf::Time&) {
	if (sprite.getPosition().x != point.x || sprite.getPosition().y != point.y) {
		if (point.x < sprite.getPosition().x && point.y < sprite.getPosition().y)
			sprite.move(-1 * spd, -1 * spd);
		else if (point.x < sprite.getPosition().x && point.y > sprite.getPosition().y)
			sprite.move(-1 * spd, 1 * spd);
		else if (point.x > sprite.getPosition().x && point.y < sprite.getPosition().y)
			sprite.move(1 * spd, -1 * spd);
		else if (point.x > sprite.getPosition().x && point.y > sprite.getPosition().y)
			sprite.move(1 * spd, 1 * spd);
		else if (point.x == sprite.getPosition().x && point.y > sprite.getPosition().y)
			sprite.move(0, 1 * spd);
		else if (point.x == sprite.getPosition().x && point.y < sprite.getPosition().y)
			sprite.move(0, -1 * spd);
		else if (point.x > sprite.getPosition().x && point.y == sprite.getPosition().y)
			sprite.move(1 * spd, 0);
		else if (point.x < sprite.getPosition().x && point.y == sprite.getPosition().y)
			sprite.move(-1 * spd, 0);
	}
}

GasterBlaster::GasterBlaster() {
	vertical = false;
	firing = false;
	start = false;
	moving = false;
	ended = false;
	activated = false;
	flipped = false;
	angle = 0;
	currentFrame = 0;
	frameWidth = 0;
	frameHeight = 0;
	frameNum = 0;
	perRow = 0;
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setPosition(5000, 5000);



	timer = 0;
}

GasterBlaster::GasterBlaster(sf::Texture& tex, bool vert, bool flip, int numFrames)
{
	sprite.setTexture(tex);
	vertical = vert;
	firing = false;
	start = false;
	moving = false;
	ended = false;
	activated = false;
	flipped = flip;
	currentFrame = 0;
	angle = 0;
	perRow = sqrt(numFrames);

	frameNum = numFrames;

	frameWidth = tex.getSize().x / perRow;
	frameHeight = tex.getSize().y / perRow;
	sprite.setPosition(5000, 5000);

	timer = 0;
	if (vertical) {
		if (flipped)
			sprite.setTextureRect(sf::IntRect(0, (perRow - 1) * frameHeight, frameWidth, frameHeight));
		else
			sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
	}
	else {
		if (flipped)
			sprite.setTextureRect(sf::IntRect((perRow - 1) * frameWidth, 0, frameWidth, frameHeight));
		else
			sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
	}
}

void GasterBlaster::fireAtPosition(float x, float y, float time, int angle, sf::Time& dT, sf::Sound& gasterSound, sf::Sound* soundQ)
{
	if (moving == false && start == false) {
		ended = false;

		bool tL = false, tR = false, bL = false, bR = false;
		if (x < 683 && y < 384)
			tL = true;
		else if (x < 683 && y > 384)
			bL = true;
		else if (x > 683 && y < 384)
			tR = true;
		else
			bR = true;

		if (tL)
			sprite.setPosition(x - 1000, y);
		else if (bL)
			sprite.setPosition(x - 1000, y);
		else if (tR)
			sprite.setPosition(x + 1000, y);
		else
			sprite.setPosition(x + 1000, y);

		moving = true;
	}
	this->angle = angle;
	sprite.setRotation(angle);
	
	if (sprite.getPosition().x != x && moving) {
		blasterMove(vector2f(x, y), sprite, 0.5, dT);
	}
	else if (sprite.getPosition().x == x) {
		moving = false;
		start = true;
	}

	if (start) {
		timer += time;
		if (currentFrame < 41)
			delay = 0.03;
		else
			delay = 0.01;
		
		if (timer >= delay) {
			int topLeft = currentFrame % perRow;
			int top = currentFrame / perRow;
			if (vertical == false) {
				if (flipped)
					sprite.setTextureRect(sf::IntRect((perRow - 1 - topLeft) * frameWidth, top * frameHeight, frameWidth, frameHeight));
				else
					sprite.setTextureRect(sf::IntRect(topLeft * frameWidth, top * frameHeight, frameWidth, frameHeight));
			}
			else {
				if (flipped)
					sprite.setTextureRect(sf::IntRect(top * frameWidth, (perRow - 1 - topLeft) * frameHeight, frameWidth, frameHeight));
				else
					sprite.setTextureRect(sf::IntRect(top * frameWidth, topLeft * frameHeight, frameWidth, frameHeight));
			}
			if (currentFrame == 1) {
				for (int i = 0; i < 10; ++i) {
					if (soundQ[i].getStatus() != sf::Sound::Playing) {
						soundQ[i].play();
						break;
					}
				}
			}
			sprite.setPosition(x, y);
			timer = 0;
			++currentFrame;
		}
		if (currentFrame == frameNum - 1) {
			start = false;
			ended = true;
			activated = false;
			currentFrame = 0;
			sprite.setPosition(5000, 5000);
		}
	}

	if (currentFrame >= 41 && currentFrame <= 80)
		firing = true;
	else
		firing = false;
}


