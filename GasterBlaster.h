#pragma once
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include <queue>

using namespace sf;

class GasterBlaster
{
	sf::Sprite sprite, laserExtension;
	bool vertical, firing, flipped;
	float timer, delay = 0.07;
	int currentFrame;
	int frameHeight, frameWidth, frameNum, perRow;
	int angle;
	bool start, moving, ended;
	bool activated;

	bool play;

public:
	GasterBlaster();
	GasterBlaster(sf::Texture& tex, bool vert = false, bool flip = false, int numFrames = 0);

	void fireAtPosition(float x, float y, float time, int ang, sf::Time&, sf::Sound&, sf::Sound*);

	void draw(sf::RenderWindow& window) { window.draw(sprite); }

	bool isOver() const { return ended; }

	sf::Sprite& getSprite() { return sprite; }

	bool isFiring() const { return firing; }

	void activate() { activated = true; }

	bool isActive() const { return activated; }

	int getAngle() const { return angle; }

	sf::FloatRect bounds() { return sprite.getGlobalBounds(); }

	bool playSound() const { return play; }
};

