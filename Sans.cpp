#include "Sans.h"

void spriteMove(vector2f point, sf::Sprite& sprite, float spd, sf::Time& dT) {
	if (sprite.getPosition().x != point.x || sprite.getPosition().y != point.y) {
		if (point.x < sprite.getPosition().x && point.y < sprite.getPosition().y)
			sprite.move(-1 * spd * dT.asSeconds() * 5000, -1 * spd * dT.asSeconds() * 5000);
		else if (point.x < sprite.getPosition().x && point.y > sprite.getPosition().y)
			sprite.move(-1 * spd * dT.asSeconds() * 5000, 1 * spd * dT.asSeconds() * 5000);
		else if (point.x > sprite.getPosition().x && point.y < sprite.getPosition().y)
			sprite.move(1 * spd * dT.asSeconds() * 5000, -1 * spd * dT.asSeconds() * 5000);
		else if (point.x > sprite.getPosition().x && point.y > sprite.getPosition().y)
			sprite.move(1 * spd * dT.asSeconds() * 5000, 1 * spd * dT.asSeconds() * 5000);
		else if (point.x == sprite.getPosition().x && point.y > sprite.getPosition().y)
			sprite.move(0, 1 * spd * dT.asSeconds() * 5000);
		else if (point.x == sprite.getPosition().x && point.y < sprite.getPosition().y)
			sprite.move(0, -1 * spd * dT.asSeconds() * 5000);
		else if (point.x > sprite.getPosition().x && point.y == sprite.getPosition().y)
			sprite.move(1 * spd * dT.asSeconds() * 5000, 0);
		else if (point.x < sprite.getPosition().x && point.y == sprite.getPosition().y)
			sprite.move(-1 * spd * dT.asSeconds() * 5000, 0);
	}
}

Sans::Sans()
{
	m_health = 1;
	fightPhase = 1;
	track = 0;

	sansHead.loadFromFile("img/sans/faces/troubled.png");

	sansBody.loadFromFile("img/sans/body.png");

	sansLegs.loadFromFile("img/sans/feet.png");

	deathTex.loadFromFile("img/sans/deathSprite.png");

	sweatTex.loadFromFile("img/sans/sweat.png");
	sansSweat.setTexture(sweatTex);

	boneTex.loadFromFile("img/sans/bone.png");

	gasterTex.loadFromFile("img/sans/blastertest.png");

	idleTex.loadFromFile("img/sans/sansIdle.png");

	idle = true;
	hitBullet = false;

	idleHeadBody.setTexture(idleTex);
	idleHeadBody.setTextureRect(sf::IntRect(0, 0, 498, 482));

	idleHeadBody.setScale(0.35, 0.35);
	legs.setTexture(sansLegs);
	idleHeadBody.setPosition(620, 50);
	legs.setPosition(-5000, -5000);

	idleHeadBody.setOrigin(idleHeadBody.getGlobalBounds().width / 2, idleHeadBody.getGlobalBounds().height / 2);

	deathSprite.setTexture(deathTex);
	deathSprite.setPosition(-5000, -5000);

	idleTimer = 0;
	idleDelay = 0.1;
	idleFrame = 1;

	moveRight = true;
	moveLeft = false;
	for (int i = 0; i < 10; ++i)
		phaseSteps[i] = false;

	for (int i = 0; i < 5; ++i)
		phaseTimer[i] = 0;

	for (int i = 0; i < 2; ++i) {
		wobble[i] = false;
	}

	for (int i = 0; i < 10; ++i) {
		gasterBuffers[i].loadFromFile("sounds/gasterBlaster.ogg"); 
		gasterSounds[i].setBuffer(gasterBuffers[i]);
	}
	
}

void Sans::incPhase() {
	for (int i = 0; i < 10; ++i)
		phaseSteps[i] = false;
	for (int i = 0; i < 5; ++i)
		phaseTimer[i] = 0;
	++fightPhase;
	track = 0;
}

void Sans::draw(sf::RenderWindow& window)
{
	window.draw(idleHeadBody);
	for (int i = 0; i < 2; ++i)
		window.draw(swapHeadBody[i]);
	for (int i = 0; i < gasters.size(); ++i)
		gasters[i].draw(window);
	for (int i = 0; i < bones.size(); ++i)
		window.draw(bones[i]);
	window.draw(legs);
	window.draw(sansSweat);
	window.draw(deathSprite);
}

bool Sans::collided(sf::Sprite other, int xOffset, int yOffset)
{
	if ((sprite.getPosition().x + sprite.getTexture()->getSize().x - xOffset >= other.getPosition().x
		&& sprite.getPosition().y + sprite.getTexture()->getSize().y - yOffset >= other.getPosition().y)
		&& (sprite.getPosition().x + xOffset <= other.getPosition().x + other.getTexture()->getSize().x
			&& sprite.getPosition().y + yOffset <= other.getPosition().y + other.getTexture()->getSize().y))
		return 1;
	else
		return 0;
}

void Sans::animateSans(float& time)
{
	if (idle) {
		idleTimer += time;
		if (idleTimer >= idleDelay) {
			idleHeadBody.setTexture(idleTex);
			idleHeadBody.setTextureRect(sf::IntRect(idleFrame * 498, 0, 498, 482));

			swapHeadBody[0].setPosition(5000, 5000);
			swapHeadBody[1].setPosition(5000, 5000);
			idleHeadBody.setScale(0.35, 0.35);
			if (idleFrame == 0)
				idleHeadBody.setPosition(idleHeadBody.getPosition().x - 15, idleHeadBody.getPosition().y + 20);
			idleTimer = 0;
			++idleFrame;

			storePos.x = idleHeadBody.getPosition().x;
			storePos.y = idleHeadBody.getPosition().y;
		}
		if (idleFrame == 12)
			idleFrame = 1;
	}
}

void Sans::phaseOne(float& timer, Player* p, sf::Time& dT)
{
	if (fightPhase == 1) {
		Sprite temp;
		p->speed = 0.1;
		temp.setTexture(boneTex);
		if (bones.size() == 0 && phaseSteps[0] == false)
			for (int i = 0; i < 38; ++i) {
				bones.push_back(temp);
			}

		if (phaseSteps[9] == false) {
			for (int i = 0; i < bones.size(); ++i)
				bones[i].setPosition(-5000, -5000);
			phaseSteps[9] = true;
		}

		if (phaseSteps[0] == false)
			for (int i = 0; i < 6; ++i) {
				bones[i].setPosition(-2000 - (i * 50), -300 + (i * 30));
				bones[6 + i].setPosition(-2000 - (i * 50), bones[i].getPosition().y + 180 + bones[i].getGlobalBounds().height);
				phaseSteps[0] = true;
			}

		if (phaseSteps[1] == false && phaseSteps[0] == true)
			for (int i = 0; i < 13; ++i) {
				bones[12 + i].setPosition(-2350 - (i * 50), -150 - (i * 30));
				bones[25 + i].setPosition(-2350 - (i * 50), bones[12 + i].getGlobalBounds().height + 180 + bones[12 + i].getPosition().y);
			}

		if (phaseSteps[0] = true)
			phaseTimer[4] += timer;
		if (phaseTimer[4] >= 2)
			phaseSteps[1] = true;

		for (int i = 0; i < bones.size(); ++i)
			bones[i].move(0.1 * dT.asSeconds() * 5000, 0);

		if (bones[bones.size() - 1].getPosition().x >= 1400 && phaseSteps[2] == false)
			phaseSteps[2] = true;

		if (gasters.size() == 0 && phaseSteps[2] == true && phaseSteps[3] == false) {
			GasterBlaster temp(gasterTex, false, false, 100);
			for (int i = 0; i < 4; ++i)
				gasters.push_back(temp);
			phaseSteps[3] = true;
		}

		if (phaseSteps[3] == true) {
			phaseTimer[0] += timer;
		}

		if (phaseTimer[0] >= 1 && phaseSteps[3] == true && phaseSteps[4] == false)
			for (int i = 0; i < 4; ++i)
				gasters[i].fireAtPosition(150, 0 + 120 * i, timer, 0, dT, gasterSound, gasterSounds);

		if (phaseTimer[0] >= 1 && phaseSteps[4] == false && gasters[0].isOver()) {

			phaseTimer[0] = 0;
			phaseSteps[4] = true;
		}

		if (phaseSteps[4] == true)
			phaseTimer[1] += timer;

		if (phaseTimer[1] >= 1 && phaseSteps[4] == true && phaseSteps[5] == false) {
			gasters[0].fireAtPosition(400, 0, timer, 90, dT, gasterSound, gasterSounds);
			gasters[1].fireAtPosition(700, 0, timer, 90, dT, gasterSound, gasterSounds);
			gasters[2].fireAtPosition(1000, 0, timer, 90, dT, gasterSound, gasterSounds);
			gasters[3].fireAtPosition(1300, 0, timer, 90, dT, gasterSound, gasterSounds);
		}

		if (phaseTimer[1] >= 1 && phaseSteps[4] == true && phaseSteps[5] == false && gasters[0].isOver()) {

			phaseTimer[1] = 0;
			phaseSteps[5] = true;
		}

		if (phaseSteps[5] == true) {
			phaseTimer[2] += timer;
		}

		if (phaseTimer[2] >= 1 && phaseSteps[5] == true && phaseSteps[6] == false) {
			gasters[0].fireAtPosition(200, 120, timer, 0, dT, gasterSound, gasterSounds);
			gasters[1].fireAtPosition(650, 70, timer, 90, dT, gasterSound, gasterSounds);
			gasters[2].fireAtPosition(1400, 800, timer, 180, dT, gasterSound, gasterSounds);
			gasters[3].fireAtPosition(900, 700, timer, 270, dT, gasterSound, gasterSounds);
		}

		if (phaseTimer[2] >= 1 && phaseSteps[5] == true && phaseSteps[6] == false && gasters[0].isOver()) {
			phaseSteps[6] = true;
			phaseTimer[2] = 0;
		}

		if (phaseSteps[6] == true)
			phaseTimer[3] += timer;

		if (phaseTimer[3] >= 1 && phaseSteps[6] == true) {
			gasters[0].fireAtPosition(100, 250, timer, 0, dT, gasterSound, gasterSounds);
			gasters[1].fireAtPosition(900, 50, timer, 90, dT, gasterSound, gasterSounds);
			gasters[2].fireAtPosition(1200, 650, timer, 180, dT, gasterSound, gasterSounds);
			gasters[3].fireAtPosition(400, 900, timer, 270, dT, gasterSound, gasterSounds);
		}

		if (phaseTimer[3] >= 1 && gasters[0].isOver()) {
			incPhase();
		}
	}
}

void Sans::phaseTwo(float& timer, sf::Time& dT) {
	if (fightPhase == 2) {
		Sprite temp;
		temp.setTexture(boneTex);
		if (bones.size() == 1)
			bones.erase(0);

		if (bones.size() == 0 && phaseSteps[0] == false)
			for (int i = 0; i < 30; ++i) {
				bones.push_back(temp);
			}

		if (phaseSteps[0] == false) {
			for (int i = 0; i < 15; ++i) {
				int n = rand() % 4;
				if (n == 0)
					bones[i].setPosition(i * -600, -500);
				else if (n == 1)
					bones[i].setPosition(i * -600, -350);
				else if (n == 2)
					bones[i].setPosition(i * -600, -250);
				else
					bones[i].setPosition(i * -600, -100);
			}
			phaseSteps[0] = true;
		}

		if (phaseSteps[1] == false) {
			for (int i = 0; i < 15; ++i) {
				bones[15 + i].setPosition(bones[i].getPosition().x, bones[i].getPosition().y + bones[i].getTexture()->getSize().y + 160);
			}
			phaseSteps[1] = true;
		}

		for (int i = 0; i < bones.size(); ++i)
			spriteMove(vector2f(1400, bones[i].getPosition().y), bones[i], 0.2, dT);

		if (phaseSteps[0] == true && phaseSteps[1] == true && bones[bones.size() - 1].getPosition().x >= 1400)
			bones.erase(bones.size() - 1);

		if (bones.size() == 1) {
			incPhase();
		}
	}
}

void Sans::phaseThree(float& timer, Player* p, sf::Time& dT) {
	if (fightPhase == 3) {
		p->canMoveHoriz = false;
		Sprite temp;
		temp.setTexture(boneTex);
		if (bones.size() == 1)
			bones.erase(0);

		if (bones.size() == 0 && phaseSteps[0] == false)
			for (int i = 0; i < 60; ++i) {
				bones.push_back(temp);
			}

		if (phaseSteps[0] == false) {
			for (int i = 0; i < 20; ++i) {
				bones[i].setPosition(300, -300 - (i * 820));
				bones[i].setScale(0.6, 0.6);
			}
			for (int i = 0; i < 20; ++i) {
				bones[20 + i].setPosition(900, -300 - (i * 820));
				bones[20 + i].setScale(0.6, 0.6);
			}
			for (int i = 0; i < 20; ++i) {
				bones[40 + i].setPosition(600, -300 - (i * 770));
				bones[40 + i].setScale(0.7, 0.7);
			}
			p->sprite.setPosition(10, 350);
			phaseSteps[0] = true;
			phaseSteps[1] = true;
		}

		if (phaseSteps[1] == true) {
			p->sprite.move(0.1 * dT.asSeconds() * 5000, 0);
			if (p->sprite.getPosition().x > 1350) {
				phaseSteps[1] = false;
				phaseSteps[2] = true;
			}
		}

		if (phaseSteps[2] == true) {
			p->sprite.move(-0.1 * dT.asSeconds() * 5000, 0);
			if (p->sprite.getPosition().x < 10) {
				phaseSteps[1] = true;
				phaseSteps[2] = false;
			}
		}

		for (int i = 0; i < 20; ++i) {
			spriteMove(vector2f(bones[i].getPosition().x, 900), bones[i], 0.12, dT);
			spriteMove(vector2f(bones[20 + i].getPosition().x, 900), bones[20 + i], 0.12, dT);
			spriteMove(vector2f(bones[40 + i].getPosition().x, 900), bones[40 + i], 0.13, dT);
		}

		if (bones[bones.size() - 1].getPosition().y > 768) {
			p->canMoveHoriz = true;
			incPhase();
		}
	}

}

void Sans::phaseFour(float& timer, sf::Time& dT) {
	if (fightPhase == 4) {

		for (int i = 0; i < bones.size(); ++i)
			bones[i].setPosition(5000, 5000);

		if (phaseSteps[0] == false) {
			GasterBlaster tmp(gasterTex, false, false, 100);
			for (int i = 0; i < 28; ++i)
				gasters.push_back(tmp);
			phaseSteps[0] = true;
		}

		if (phaseSteps[0] == true)
			phaseTimer[1] += timer;

		if (phaseTimer[1] >= 0.2 && track <= 23 && phaseSteps[2] == false) {
			int n = rand() % 6;
			if (n == 0)
				gasterPos = vector2f(500, 100);
			else if (n == 1)
				gasterPos = vector2f(600, 100);
			else if (n == 2)
				gasterPos = vector2f(700, 100);
			else if (n == 3)
				gasterPos = vector2f(800, 100);
			else if (n == 4)
				gasterPos = vector2f(900, 100);
			else if (n == 5)
				gasterPos = vector2f(1000, 100);
			phaseSteps[2] = true;
		}

		if (phaseTimer[1] >= 0.2 && phaseSteps[2] == true) {
			gasters[track].fireAtPosition(gasterPos.x, gasterPos.y, timer, 90, dT, gasterSound, gasterSounds);

			gasters[track + 1].fireAtPosition(gasterPos.x + 500, gasterPos.y, timer, 90, dT, gasterSound, gasterSounds);

			if (gasterPos.x <= 400)
				gasters[track + 2].fireAtPosition(gasterPos.x - 300, gasterPos.y + 100, timer, 0, dT, gasterSound, gasterSounds);
			else if (gasterPos.x <= 600)
				gasters[track + 2].fireAtPosition(gasterPos.x - 300, gasterPos.y + 200, timer, 0, dT, gasterSound, gasterSounds);
			else
				gasters[track + 2].fireAtPosition(gasterPos.x - 300, gasterPos.y + 300, timer, 0, dT, gasterSound, gasterSounds);
			gasters[track + 3].fireAtPosition(gasterPos.x + 500, gasterPos.y + 400, timer, 180, dT, gasterSound, gasterSounds);

		}

		if (track <= 23 && gasters[track].isOver()) {
			phaseTimer[1] = 0;
			phaseSteps[2] = false;
			track += 4;
		}

		if (track > 23) {
			incPhase();

		}

	}
}

void Sans::phaseFive(float& timer, sf::RenderWindow& window, Player* p, sf::Time& dT) {
	if (fightPhase == 5) {
		if (phaseSteps[9] == false) {
			for (int i = 0; i < bones.size(); ++i) {
				bones[i].setPosition(-5000, -5000);
				bones[i].setScale(1, 1);
			}
			phaseSteps[9] = true;
		}

		if (phaseSteps[0] == false)
			phaseTimer[0] += timer;

		if (phaseTimer[0] >= 1 && phaseSteps[0] == false) {
			window.clear(Color::Black);
		}
		if (phaseTimer[0] >= 1.4) {
			phaseSteps[0] = true;
			phaseTimer[0] = 0;
		}

		if (phaseSteps[0] == true && phaseSteps[1] == false) {
			if (bones.size() < 2) {
				Sprite tmp(boneTex);
				while (bones.size() < 2)
					bones.push_back(tmp);
			}
			p->sprite.setPosition(1000, 600);
			bones[0].setPosition(300, -400);
			bones[1].setPosition(300, 300);
			phaseSteps[1] = true;
		}

		if (phaseSteps[1] == true && phaseSteps[2] == false) {
			for (int i = 0; i < 2; ++i)
				bones[i].move(0.2 * dT.asSeconds() * 5000, 0);
		}

		if (bones[0].getPosition().x > 1400 && phaseSteps[1] == true)
			phaseSteps[2] = true;

		if (phaseSteps[2] == true) {
			phaseTimer[1] += timer;
		}

		if (phaseTimer[1] >= 0.2 && phaseSteps[3] == false) {
			window.clear(Color::Black);
		}
		if (phaseTimer[1] >= 0.6 && phaseSteps[3] == false) {
			phaseSteps[3] = true;
			phaseTimer[1] = 0;
		}

		if (phaseSteps[3] == true && phaseSteps[4] == false) {
			if (bones.size() < 6) {
				Sprite tmp(boneTex);
				while (bones.size() < 6)
					bones.push_back(tmp);
			}
			p->sprite.setPosition(10, 350);
			p->canMoveHoriz = false;
			for (int i = 0; i < 2; ++i) {
				bones[i].setPosition(300, -300 - (i * 820));
				bones[i].setScale(0.6, 0.6);
			}
			for (int i = 0; i < 2; ++i) {
				bones[2 + i].setPosition(900, -300 - (i * 820));
				bones[2 + i].setScale(0.6, 0.6);
			}
			for (int i = 0; i < 2; ++i) {
				bones[4 + i].setPosition(600, -300 - (i * 770));
				bones[4 + i].setScale(0.7, 0.7);
			}
			phaseSteps[4] = true;
		}

		if (phaseSteps[4] == true && phaseSteps[5] == false) {
			p->sprite.move(0.15 * dT.asSeconds() * 5000, 0);
			for (int i = 0; i < 2; ++i) {
				bones[i].move(0, 0.15 * dT.asSeconds() * 5000);
				bones[2 + i].move(0, 0.15 * dT.asSeconds() * 5000);
				bones[4 + i].move(0, 0.2 * dT.asSeconds() * 5000);
			}
		}
		if (p->sprite.getPosition().x > 1250 && phaseSteps[4] == true) {
			phaseSteps[5] = true;
			for (int i = 0; i < 6; ++i) {
				bones[i].setPosition(5000, 5000);
			}
		}
		if (phaseSteps[5] == true) {
			phaseTimer[2] += timer;
		}
		if (phaseTimer[2] >= 0.2 && phaseSteps[6] == false) {
			window.clear(Color::Black);
		}
		if (phaseTimer[2] >= 0.6 && phaseSteps[6] == false) {
			phaseSteps[6] = true;
			phaseTimer[2] = 0;
			p->canMoveHoriz = true;
			p->sprite.setPosition(10, 200);
		}

		if (phaseSteps[6] == true && phaseSteps[7] == false) {
			Sprite tmp(boneTex);
			while (bones.size() < 85) {
				bones.push_back(tmp);
			}
		}

		if (phaseSteps[6] == true && phaseSteps[7] == false) {
			for (int i = 0; i < 3; ++i) {
				bones[i].setScale(1, 1);
				bones[3 + i].setScale(1, 1);
				bones[i].setPosition(1000 + (i * 50), -300 + i * 7);
				bones[3 + i].setPosition(1000 + (i * 50), bones[i].getPosition().y + 180 + bones[i].getGlobalBounds().height);
			}
			for (int i = 0; i < 15; ++i) {
				bones[i].setScale(1, 1);
				bones[21 + i].setScale(1, 1);
				bones[6 + i].setPosition(1150 + (i * 50), -270 + (i * 20));
				bones[21 + i].setPosition(1150 + (i * 50), bones[6 + i].getPosition().y + 180 + bones[6 + i].getGlobalBounds().height);
			}
			for (int i = 0; i < 10; ++i) {
				bones[36 + i].setPosition(1900 + (i * 50), -10);
				bones[46 + i].setPosition(1900 + (i * 50), bones[36 + i].getPosition().y + 180 + bones[36 + i].getGlobalBounds().height);
			}
			for (int i = 0; i < 10; ++i) {
				bones[55 + i].setPosition(2400 + (i * 50), -20 - (i * 30));
				bones[65 + i].setPosition(2400 + (i * 50), bones[55 + i].getPosition().y + 180 + bones[55 + i].getGlobalBounds().height);
			}
			for (int i = 0; i < 5; ++i) {
				bones[75 + i].setPosition(2900 + (i * 50), -310 - (20 * i));
				bones[80 + i].setPosition(2900 + (i * 50), bones[75 + i].getPosition().y + 180 + bones[75 + i].getGlobalBounds().height);
			}
			phaseSteps[7] = true;
		}

		if (phaseSteps[7] == true) {
			for (int i = 0; i < 85; ++i) {
				bones[i].move(-0.2 * dT.asSeconds() * 5000, 0);
			}
		}
		if (phaseSteps[7] == true && bones[bones.size() - 1].getPosition().x < -100) {
			phaseSteps[8] = true;
		}
		if (phaseSteps[8] == true) {
			incPhase();
		}

	}
}

void Sans::phaseSix(float& timer, sf::RenderWindow& window, Player* p, sf::Time& dT) {
	if (fightPhase == 6) {

		if (phaseSteps[9] == false) {
			for (int i = 0; i < bones.size(); ++i)
				bones[i].setPosition(-5000, -5000);
		}

		if (phaseSteps[0] == false) {
			while (gasters.size() < 20) {
				GasterBlaster temp(gasterTex, false, false, 100);
				gasters.push_back(temp);
			}
			phaseSteps[0] = true;
		}


		if (phaseSteps[1] == false) {
			phaseTimer[0] += timer;
		}

		if (phaseTimer[0] >= 0.2 && phaseSteps[1] == false) {
			window.clear(Color::Black);
		}
		if (phaseTimer[0] >= 0.6) {
			phaseSteps[1] = true;
			phaseSteps[2] = true;
			phaseTimer[0] = 0;
			p->sprite.setPosition(400, 200);
		}

		if (phaseSteps[2] == true) {
			phaseTimer[1] += timer;
		}
		if (phaseTimer[1] >= 0.8 && track < 20) {
			gasters[track].activate();
			phaseTimer[1] = 0;
			++track;
			if (track >= 20)
				phaseSteps[4] = true;
		}
		for (int i = 0; i < 20; ++i) {
			if (gasters[i].isActive()) {
				if (i < 5)
					gasters[i].fireAtPosition(250, -150 + (i * 150), timer, 0, dT, gasterSound, gasterSounds);
				else if (i >= 5 && i < 10)
					gasters[i].fireAtPosition(-300 + (i * 200), 100, timer, 90, dT, gasterSound, gasterSounds);
				else if (i >= 10 && i < 15)
					gasters[i].fireAtPosition(1000, 950 - (i % 10) * 150, timer, 180, dT, gasterSound, gasterSounds);
				else
					gasters[i].fireAtPosition(600 - (i % 15) * 200, 700, timer, 270, dT, gasterSound, gasterSounds);
			}
		}
		if (phaseSteps[4] == true && gasters[19].isOver() && track >= 20) {
			phaseSteps[3] = true;
		}
		if (phaseSteps[3] == true) {
			incPhase();
		}
	}
}

void Sans::phaseSeven(float& timer, sf::RenderWindow& window, Player* p, sf::Time& dT) {
	if (fightPhase == 7) {

		if (bones.size() < 4) {
			Sprite temp(boneTex);
			for (int i = 0; i < 4; ++i) {
				bones.push_back(temp);
				bones[i].setPosition(-5000, -5000);
			}
		}

		if (phaseSteps[0] == false)
			phaseTimer[0] += timer;

		if (phaseTimer[0] >= 1 && phaseSteps[0] == false) {
			window.clear(Color::Black);
			bones[0].setPosition(0, -300);
			bones[1].setPosition(0, 460);
			bones[2].setPosition(1366, -300);
			bones[3].setPosition(1366, 460);
		}

		if (phaseTimer[0] >= 1.4) {
			phaseSteps[0] = true;
			p->sprite.setPosition(600, 600);
			phaseTimer[0] = 0;
		}

		if (phaseSteps[0] == true && phaseSteps[1] == false) {
			for (int i = 0; i < 2; ++i)
				bones[i].move(0.2 * dT.asSeconds() * 5000, 0);
			for (int i = 0; i < 2; ++i)
				bones[2 + i].move(-0.2 * dT.asSeconds() * 5000, 0);
		}

		if (bones[0].getPosition().x >= 1350)
			phaseSteps[1] = true;

		if (phaseSteps[1] == true && phaseSteps[2] == false) {
			window.clear(Color::Black);
			phaseTimer[0] += timer;
		}

		if (phaseSteps[1] == true && phaseSteps[2] == false) {


			if (bones.size() < 6) {
				Sprite tmp(boneTex);
				while (bones.size() < 6)
					bones.push_back(tmp);
			}
			p->sprite.setPosition(1300, 350);
			p->canMoveHoriz = false;
			for (int i = 0; i < 2; ++i) {
				bones[i].setPosition(300, -300 - (i * 820));
				bones[i].setScale(0.6, 0.6);
			}
			for (int i = 0; i < 2; ++i) {
				bones[2 + i].setPosition(900, -100 - (i * 820));
				bones[2 + i].setScale(0.6, 0.6);
			}
			for (int i = 0; i < 2; ++i) {
				bones[4 + i].setPosition(600, -300 - (i * 770));
				bones[4 + i].setScale(0.7, 0.7);
			}
		}

		if (phaseTimer[0] >= 0.4 && phaseSteps[1] == true && phaseSteps[2] == false) {
			phaseSteps[2] = true;
			phaseTimer[0] = 0;
		}

		if (phaseSteps[2] == true && phaseSteps[3] == false) {
			for (int i = 0; i < 6; ++i)
				bones[i].move(0, 0.15 * dT.asSeconds() * 5000);
			p->sprite.move(-0.12 * dT.asSeconds() * 5000, 0);
		}

		if (p->sprite.getPosition().x < 50) {
			p->canMoveHoriz = true;
			phaseSteps[3] = true;
		}

		if (phaseSteps[3] == true && phaseSteps[4] == false) {
			window.clear(Color::Black);
			phaseTimer[1] += timer;
		}
		if (phaseTimer[1] >= 0.4) {
			phaseSteps[4] = true;
		}

		if (phaseSteps[4] == true && phaseSteps[5] == false) {
			while (bones.size() < 85) {
				Sprite tmp(boneTex);
				bones.push_back(tmp);
			}
			for (int i = 0; i < 3; ++i) {
				bones[i].setScale(1, 1);
				bones[3 + i].setScale(1, 1);
				bones[i].setPosition(200 - (i * 50), -300 + i * 7);
				bones[3 + i].setPosition(200 - (i * 50), bones[i].getPosition().y + 180 + bones[i].getGlobalBounds().height);
			}
			for (int i = 0; i < 15; ++i) {
				bones[i].setScale(1, 1);
				bones[21 + i].setScale(1, 1);
				bones[6 + i].setPosition(50 - (i * 50), -270 + (i * 10));
				bones[21 + i].setPosition(50 - (i * 50), bones[6 + i].getPosition().y + 180 + bones[6 + i].getGlobalBounds().height);
			}
			for (int i = 0; i < 10; ++i) {
				bones[36 + i].setPosition(-700 - (i * 50), -120);
				bones[46 + i].setPosition(-700 - (i * 50), bones[36 + i].getPosition().y + 180 + bones[36 + i].getGlobalBounds().height);
			}
			for (int i = 0; i < 10; ++i) {
				bones[55 + i].setPosition(-1200 - (i * 50), -130 - (i * 20));
				bones[65 + i].setPosition(-1200 - (i * 50), bones[55 + i].getPosition().y + 180 + bones[55 + i].getGlobalBounds().height);
			}
			for (int i = 0; i < 5; ++i) {
				bones[75 + i].setPosition(-1700 - (i * 50), -320 - (20 * i));
				bones[80 + i].setPosition(-1700 - (i * 50), bones[75 + i].getPosition().y + 180 + bones[75 + i].getGlobalBounds().height);
			}
			p->sprite.setPosition(1000, 350);
			phaseSteps[5] = true;
		}

		if (phaseSteps[5] == true && phaseSteps[6] == false) {
			for (int i = 0; i < 85; ++i)
				bones[i].move(0.2 * dT.asSeconds() * 5000, 0);
			if (bones[84].getPosition().x >= 1350)
				phaseSteps[6] = true;
		}

		if (phaseSteps[6] == true && phaseSteps[7] == false) {
			window.clear(Color::Black);
			phaseTimer[2] += timer;
		}

		if (phaseTimer[2] >= 0.4 && phaseSteps[7] == false) {
			phaseSteps[7] = true;
			for (int i = 0; i < bones.size(); ++i)
				bones[i].setPosition(-5000, -5000);
		}

		if (phaseSteps[7] == true && phaseSteps[8] == false) {
			p->sprite.setPosition(600, 600);
			bones[0].setPosition(0, -300);
			bones[1].setPosition(0, 460);
			bones[2].setPosition(1366, -300);
			bones[3].setPosition(1366, 460);

			phaseSteps[8] = true;
		}

		if (phaseSteps[8] == true) {
			for (int i = 0; i < 2; ++i)
				bones[i].move(0.2 * dT.asSeconds() * 5000, 0);
			for (int i = 0; i < 2; ++i)
				bones[2 + i].move(-0.2 * dT.asSeconds() * 5000, 0);
		}

		if (bones[0].getPosition().x >= 1360 && phaseSteps[8] == true) {
			p->canMoveHoriz = true;
			incPhase();
		}
	}
}

void Sans::phaseEight(float& timer, sf::RenderWindow& window, Player* p, sf::Time& dT) {
	if (fightPhase == 8) {

		if (phaseSteps[0] == false) {
			phaseTimer[0] += timer;
		}

		if (phaseSteps[9] == false) {
			for (int i = 0; i < bones.size(); ++i)
				bones[i].setPosition(-5000, -5000);
			phaseSteps[9] = true;
		}

		if (phaseTimer[0] >= 0.2 && phaseSteps[0] == false) {
			window.clear(Color::Black);
			for (int i = 0; i < bones.size(); ++i)
				bones[i].setPosition(-5000, -5000);
			while (gasters.size() < 4) {
				GasterBlaster temp(gasterTex, false, false, 100);
				gasters.push_back(temp);
			}
		}

		if (phaseTimer[0] >= 0.6 && phaseSteps[0] == false) {
			phaseSteps[0] = true;
			p->sprite.setPosition(683, 384);
			for (int i = 0; i < 4; ++i)
				gasters[i].activate();
		}

		for (int i = 0; i < gasters.size(); ++i) {
			if (gasters[i].isActive() && phaseSteps[7] == false) {
				if (i == 0)
					gasters[i].fireAtPosition(200, 200, timer, 0, dT, gasterSound, gasterSounds);
				else if (i == 1)
					gasters[i].fireAtPosition(900, 100, timer, 90, dT, gasterSound, gasterSounds);
				else if (i == 2)
					gasters[i].fireAtPosition(1300, 680, timer, 180, dT, gasterSound, gasterSounds);
				else
					gasters[i].fireAtPosition(550, 700, timer, 270, dT, gasterSound, gasterSounds);

				if (i == 3 && gasters[i].isOver())
					phaseSteps[1] = true;
			}
		}

		if (phaseSteps[1] == true && phaseSteps[2] == false) {
			phaseTimer[1] += timer;
		}

		if (phaseTimer[1] >= 0.2 && phaseSteps[2] == false) {
			window.clear(Color::Black);
		}

		if (phaseTimer[1] >= 0.6) {
			phaseTimer[1] = 0;
			phaseSteps[2] = true;
			p->sprite.setPosition(0, 350);
		}

		if (phaseSteps[2] == true && phaseSteps[3] == false) {
			while (bones.size() < 100) {
				Sprite temp(boneTex);
				bones.push_back(temp);
			}

			for (int i = 0; i < 5; ++i) {
				bones[i].setPosition(1200 + (i * 100), -400 + (i * 50));
				bones[5 + i].setPosition(1200 + (i * 100), bones[i].getPosition().y + 180 + bones[i].getGlobalBounds().height);
			}
			for (int i = 0; i < 5; ++i) {
				bones[10 + i].setPosition(1700 + (i * 100), -200 - (i * 50));
				bones[15 + i].setPosition(1700 + (i * 100), bones[10 + i].getPosition().y + 180 + bones[i].getGlobalBounds().height);
			}
			for (int i = 0; i < 5; ++i) {
				bones[20 + i].setPosition(2200 + (i * 100), -400 + (i * 50));
				bones[25 + i].setPosition(2200 + (i * 100), bones[20 + i].getPosition().y + 180 + bones[i].getGlobalBounds().height);
			}
			for (int i = 0; i < 5; ++i) {
				bones[30 + i].setPosition(2700 + (i * 100), -200 - (i * 50));
				bones[35 + i].setPosition(2700 + (i * 100), bones[30 + i].getPosition().y + 180 + bones[i].getGlobalBounds().height);
			}
			for (int i = 0; i < 5; ++i) {
				bones[40 + i].setPosition(3200 + (i * 100), -400 + (i * 50));
				bones[45 + i].setPosition(3200 + (i * 100), bones[40 + i].getPosition().y + 180 + bones[i].getGlobalBounds().height);
			}
			for (int i = 0; i < 5; ++i) {
				bones[50 + i].setPosition(3700 + (i * 100), -200 - (i * 50));
				bones[55 + i].setPosition(3700 + (i * 100), bones[50 + i].getPosition().y + 180 + bones[i].getGlobalBounds().height);
			}
			for (int i = 0; i < 5; ++i) {
				bones[60 + i].setPosition(4200 + (i * 100), -400 + (i * 50));
				bones[65 + i].setPosition(4200 + (i * 100), bones[60 + i].getPosition().y + 180 + bones[i].getGlobalBounds().height);
			}
			for (int i = 0; i < 5; ++i) {
				bones[70 + i].setPosition(4700 + (i * 100), -200 - (i * 50));
				bones[75 + i].setPosition(4700 + (i * 100), bones[70 + i].getPosition().y + 180 + bones[i].getGlobalBounds().height);
			}
			for (int i = 0; i < 5; ++i) {
				bones[80 + i].setPosition(5200 + (i * 100), -400 + (i * 50));
				bones[85 + i].setPosition(5200 + (i * 100), bones[80 + i].getPosition().y + 180 + bones[i].getGlobalBounds().height);
			}
			for (int i = 0; i < 5; ++i) {
				bones[90 + i].setPosition(5700 + (i * 100), -200 - (i * 50));
				bones[95 + i].setPosition(5700 + (i * 100), bones[90 + i].getPosition().y + 180 + bones[i].getGlobalBounds().height);
			}

			phaseSteps[3] = true;
		}

		if (phaseSteps[3] == true && phaseSteps[4] == false) {
			for (int i = 0; i < 100; ++i)
				bones[i].move(-0.2 * dT.asSeconds() * 5000, 0);

			if (bones[99].getPosition().x < -50) {
				phaseSteps[4] = true;
			}
		}

		if (phaseSteps[4] == true && phaseSteps[5] == false) {
			for (int i = 0; i < 25; ++i) {
				bones[i].setPosition(1400 + (i * 100), -590 + (i * 12.15));
				bones[25 + i].setPosition(1400 + (i * 100), 750 - (i * 12.15));
			}
			phaseSteps[5] = true;
		}

		if (phaseSteps[5] == true) {
			for (int i = 0; i < 50; ++i) {
				bones[i].move(-0.2 * dT.asSeconds() * 5000, 0);
			}
		}

		if (phaseSteps[5] == true && bones[49].getPosition().x < -50) {
			phaseSteps[6] = true;
			for (int i = 0; i < bones.size(); ++i)
				bones[i].setPosition(-5000, -5000);
		}

		if (phaseSteps[6] == true && phaseSteps[7] == false) {
			phaseTimer[2] += timer;
			window.clear(Color::Black);
		}

		if (phaseTimer[2] >= 0.4) {
			phaseSteps[7] = true;
			phaseTimer[2] = 0;
			p->sprite.setPosition(1000, 380);
		}

		if (phaseSteps[7] == true) {
			phaseTimer[3] += timer;
			while (gasters.size() < 50) {
				GasterBlaster temp(gasterTex, false, false, 100);
				gasters.push_back(temp);
			}
		}

		if (phaseTimer[3] >= 0.3 && track < 50) {
			gasters[track].activate();
			phaseTimer[3] = 0;
			++track;
		}

		if (phaseSteps[7] == true)
			for (int i = 0; i < gasters.size(); ++i) {
				if (gasters[i].isActive()) {
					if (i % 20 < 5)
						gasters[i].fireAtPosition(250, -150 + (i % 20 * 150), timer, 0, dT, gasterSound, gasterSounds);
					else if (i % 20 >= 5 && i % 20 < 10)
						gasters[i].fireAtPosition(-300 + (i % 20 * 200), 100, timer, 90, dT, gasterSound, gasterSounds);
					else if (i % 20 >= 10 && i % 20 < 15)
						gasters[i].fireAtPosition(850, 950 - (i % 10) * 150, timer, 180, dT, gasterSound, gasterSounds);
					else
						gasters[i].fireAtPosition(600 - (i % 15) * 200, 700, timer, 270, dT, gasterSound, gasterSounds);
				}
			}

		if (phaseSteps[7] == true && gasters[49].isOver()) {
			phaseSteps[8] = true;
		}

		if (phaseSteps[8] == true) {
			incPhase();
		}
	}
}

void Sans::phaseNine(float& timer, Player* p, sf::Time& dT) {
	if (fightPhase == 9) {

		if (phaseSteps[1] == false)
			phaseTimer[0] += timer;
		if (phaseTimer[0] >= 1)
			phaseSteps[0] = true;

		if (phaseSteps[0] == true && phaseSteps[1] == false) {
			swapHeadBody[0].setTexture(sansHead);
			swapHeadBody[1].setTexture(sansBody);
			idle = false;
			swapHeadBody[0].setPosition(idleHeadBody.getPosition().x + 30, idleHeadBody.getPosition().y - 10);
			swapHeadBody[1].setPosition(idleHeadBody.getPosition().x + 10, idleHeadBody.getPosition().y + 40);
			legs.setPosition(idleHeadBody.getPosition().x + 22, idleHeadBody.getPosition().y + 91);
			storePos.x = swapHeadBody[0].getPosition().x;
			storePos.y = swapHeadBody[0].getPosition().y;
			sansSweat.setPosition(swapHeadBody[0].getPosition().x + 15, swapHeadBody[0].getPosition().y);
			phaseSteps[0] = true;
			idleHeadBody.setPosition(5000, 5000);
		}

		if (m_health > 0) {
			if (wobble[0] == false && wobble[1] == false) {
				wobble[0] = true;
			}
			if (wobble[0] == true) {
				if (swapHeadBody[0].getPosition().y >= storePos.y - 15) {
					for (int i = 0; i < 2; ++i)
						swapHeadBody[i].move(0, -0.01 * dT.asSeconds() * 1000);
					sansSweat.move(0, -0.01 * dT.asSeconds() * 1000);
					legs.move(0, -0.01 * dT.asSeconds() * 1000);
				}
				else {
					wobble[0] = false;
					wobble[1] = true;
				}
			}

			else if (wobble[1] == true) {
				if (swapHeadBody[0].getPosition().y <= storePos.y + 15) {
					for (int i = 0; i < 2; ++i)
						swapHeadBody[i].move(0, 0.01 * dT.asSeconds() * 1000);
					sansSweat.move(0, 0.01 * dT.asSeconds() * 1000);
					legs.move(0, 0.01 * dT.asSeconds() * 1000);
				}
				else {
					wobble[1] = false;
					wobble[0] = true;
				}
			}
		}

		if (phaseSteps[0] == true) {
			phaseSteps[1] = true;
		}
		
		if (hitBullet && phaseSteps[2] == false) {
			deathSprite.setPosition(legs.getPosition().x - 70, legs.getPosition().y - 65);
			deathSprite.setScale(0.45, 0.45);

			for (int i = 0; i < 2; ++i)
				swapHeadBody[i].setPosition(-5000, -5000);
			legs.setPosition(-5000, -5000);
			sansSweat.setPosition(-5000, -5000);

			phaseSteps[2] = true;
		}

		if (phaseSteps[2] == true) {
			m_health = 0;
			deathSprite.move(0, -0.01 * dT.asSeconds() * 5000);
			if (deathSprite.getPosition().y <= -200)
				incPhase();
		}

	}
}

void Sans::deleteGasters() {
	for (int i = 0; i < gasters.size(); ++i) {
		if (gasters[i].isOver())
			gasters.erase(i);
	}
}

void Sans::deleteBones(int index) {
	if (index > 0 && index < bones.size())
		bones.erase(index);
}

void Sans::playSounds()
{
}

bool Sans::gasterCollision(sf::Sprite& other)
{
	for (int i = 0; i < gasters.size(); ++i) {
		if (gasters[i].isFiring()) {
			if (gasters[i].getAngle() == 0) {
				if ((gasters[i].bounds().left + gasters[i].bounds().width - 50 >= other.getGlobalBounds().left &&
					gasters[i].bounds().top + gasters[i].bounds().height - 200 >= other.getGlobalBounds().top) &&
					(gasters[i].bounds().left + 150 <= other.getGlobalBounds().left + other.getGlobalBounds().width &&
						gasters[i].bounds().top + 230 <= other.getGlobalBounds().top + other.getGlobalBounds().height)) {
					return 1;
				}
			}
			else if (gasters[i].getAngle() == 90) {
				if ((gasters[i].bounds().left + gasters[i].bounds().width - 200 >= other.getGlobalBounds().left &&
					gasters[i].bounds().top + gasters[i].bounds().height - 50 >= other.getGlobalBounds().top) &&
					(gasters[i].bounds().left + 230 <= other.getGlobalBounds().left + other.getGlobalBounds().width &&
						gasters[i].bounds().top + 150 <= other.getGlobalBounds().top + other.getGlobalBounds().height)) {
					return 1;
				}
			}
			else if (gasters[i].getAngle() == 180) {
				if ((gasters[i].bounds().left + gasters[i].bounds().width - 50 >= other.getGlobalBounds().left &&
					gasters[i].bounds().top + gasters[i].bounds().height - 200 >= other.getGlobalBounds().top) &&
					(gasters[i].bounds().left + 50 <= other.getGlobalBounds().left + other.getGlobalBounds().width &&
						gasters[i].bounds().top + 230 <= other.getGlobalBounds().top + other.getGlobalBounds().height)) {
					return 1;
				}
			}
			else if (gasters[i].getAngle() == 270) {
				if ((gasters[i].bounds().left + gasters[i].bounds().width - 200 >= other.getGlobalBounds().left &&
					gasters[i].bounds().top + gasters[i].bounds().height - 150 >= other.getGlobalBounds().top) &&
					(gasters[i].bounds().left + 230 <= other.getGlobalBounds().left + other.getGlobalBounds().width &&
						gasters[i].bounds().top + 150 <= other.getGlobalBounds().top + other.getGlobalBounds().height)) {
					return 1;
				}
			}
		}
	}
	return 0;
}

bool Sans::boneCollision(sf::Sprite& other)
{
	for (int i = 0; i < bones.size(); ++i) {
		if ((bones[i].getPosition().x + bones[i].getGlobalBounds().width >= other.getPosition().x
			&& bones[i].getPosition().y + bones[i].getGlobalBounds().height - 90 >= other.getPosition().y)
			&& (bones[i].getPosition().x <= other.getPosition().x + other.getTextureRect().width
				&& bones[i].getPosition().y + 60 <= other.getPosition().y + other.getTextureRect().height)) {
			return 1;
		}
	}
	return 0;
}

void Sans::dodgeSans(sf::Sprite& other, float& time, sf::Time& dT) {

	if ((idleHeadBody.getPosition().x + 130 >= other.getPosition().x)
		&& (idleHeadBody.getPosition().y + 190 >= other.getPosition().y)
		&& (idleHeadBody.getPosition().x <= other.getPosition().x + other.getTexture()->getSize().x
			&& idleHeadBody.getPosition().y <= other.getPosition().y + other.getTexture()->getSize().y)) {


		if (idleHeadBody.getPosition().x >= 1200) {
			moveRight = false;
			moveLeft = true;
		}

		if (idleHeadBody.getPosition().x <= 150) {
			moveLeft = false;
			moveRight = true;
		}

		if (moveRight == true) {
			spriteMove(vector2f(other.getPosition().x + 500, idleHeadBody.getPosition().y), idleHeadBody, 0.5, dT);
		}

		else if (moveLeft) {
			spriteMove(vector2f(other.getPosition().x - 500, idleHeadBody.getPosition().y), idleHeadBody, 0.5, dT);
		}
	}
}
