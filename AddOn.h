#pragma once
#include <SFML/Graphics.hpp>
#include "vector2f.h"
class AddOn
{
protected:
	sf::Sprite sprite;
	vector2f pos;
	float spd = 0.1;

public:
	AddOn(sf::Texture& tex);
	virtual int addonType() = 0;
	void setPos(float x, float y) { sprite.setPosition(x, y); }
	void move(float x, float y) { sprite.move(x, y); }
	vector2f getPos() {
		pos.x = sprite.getPosition().x;
		pos.y = sprite.getPosition().y;
		return pos;
	}
	sf::Sprite& getSprite() { return sprite; }
};

class Danger : public AddOn {
public:
	Danger(sf::Texture& tex) : AddOn(tex) {}
	virtual int addonType() override { return 1; }
};

class PowerUp : public AddOn {
public:
	PowerUp(sf::Texture& tex) : AddOn(tex) {}
	virtual int addonType() override { return 2; }
};

class Fire : public AddOn {
public:
	Fire(sf::Texture& tex) : AddOn(tex) {}
	virtual int addonType() override { return 3; }
};

class Life : public AddOn {
public:
	Life(sf::Texture& tex) : AddOn(tex) {}
	virtual int addonType() override { return 4; }
};