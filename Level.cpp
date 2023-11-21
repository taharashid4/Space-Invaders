#include "Level.h"

Level::Level()
{
	curLevel = 1;
	phase = 0;
	changingPhase = false;
	sansLevel = false;
	font.loadFromFile("fonts/comicsans.ttf");
	text.setFont(font);
	text.setCharacterSize(25);
	playingAnim = true;
	playingBomb = false;
	shape = "rectangle";
}

void Level::reset() {
	curLevel = 1;
	phase = 0;
	changingPhase = false;
	sansLevel = false;
	playingAnim = true;
	playingBomb = false;
	shape = "rectangle";
}

void Level::incPhase()
{
	++phase;
	bool changetoSans = true;
	if (sansLevel) {
		sansLevel = false;
		changetoSans = false;
	}
	if (phase > 3 && curLevel < 3) {
		phase = 1;
		++curLevel;
	}
	playingAnim = true;
	if (curLevel == 1 && phase == 1)
		shape = "rectangle";
	else if (curLevel == 1 && phase == 2)
		shape = "triangle";
	else if (curLevel == 1 && phase == 3)
		shape = "cross";
	else if (curLevel == 2 && phase == 1)
		shape = "circle";
	else if (curLevel == 2 && phase == 2)
		shape = "diamond";
	else if (curLevel == 2 && phase == 3)
		shape = "heart";
	else if (curLevel == 3) {
		int n = rand() % 10;
		if (n >= 8 && changetoSans == false) {
			while (n >= 8)
				n = rand() % 10;
		}
		playingAnim = true;
		if (n == 0)
			shape = "rectangle";
		else if (n == 1)
			shape = "triangle";
		else if (n == 2)
			shape = "cross";
		else if (n == 3)
			shape = "circle";
		else if (n == 4)
			shape = "diamond";
		else if (n == 5)
			shape = "heart";
		else if (n < 8)
			shape = "rectangle";
		else if (n >= 8) {
			// shape = "triangle";
		playingAnim = false; // activate for Sans
		changingPhase = false;
		sansLevel = true;

		}
	}
}

int Level::shapeNum() const {
	if (shape == "rectangle" && curLevel < 3)
		return 24;
	else if (shape == "triangle" && curLevel < 3)
		return 28;

	else if (shape == "circle" && curLevel < 3)
		return 14;
	else if (shape == "diamond" && curLevel < 3)
		return 20;
	else if (shape == "heart" && curLevel < 3)
		return 18;

	else if (shape == "cross")
		return 21;
	else if (shape == "rectangle" && curLevel >= 3)
		return 40;
	else if (shape == "triangle" && curLevel >= 3)
		return 43;
	else if (shape == "circle" && curLevel >= 3)
		return 24;
	else if (shape == "diamond" && curLevel >= 3)
		return 33;
	else if (shape == "heart" && curLevel >= 3)
		return 25;
}

void Level::draw(sf::RenderWindow& window)
{
	if (sansLevel == false)
		text.setString("* level " + std::to_string(curLevel));
	else
		text.setString("* bad time.");
	text.setPosition(90, 680);
	window.draw(text);
}
