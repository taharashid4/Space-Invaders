#pragma once
#include "SFML/Graphics.hpp"
#include <string>

class Level
{
	int curLevel, phase;
	std::string shape;
	bool changingPhase, playingAnim, playingBomb;
	bool sansLevel;
	sf::Text text;
	sf::Font font;

public:
	Level();
	bool changing() const { return changingPhase; }
	void setChange(bool change) { changingPhase = change; }
	void incPhase();
	bool animating() const { return playingAnim; }
	void setAnim(bool anim) { playingAnim = anim; }
	int getLevel() const { return curLevel; }
	int getPhase() const { return phase; }
	int shapeNum() const;
	bool playBomb() const { return playingBomb; }
	void setBomb(bool bomb) { playingBomb = bomb; }
	std::string getShape() const { return shape; }
	void setShape(std::string str) { shape = str; }

	bool sans() const { return sansLevel; }
	void setSans(bool n) { sansLevel = n; }
	void reset();
	void draw(sf::RenderWindow& window);
};

