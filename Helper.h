#pragma once
#include "iostream"
#include "Game.h"
#include "Level.h"
#include "AddOn.h"
#include "vector2f.h"

enum headSprites {
	badTime,
	lookingRight,
	normal,
	wink,
	HEAD_NUM
};

using namespace std;

void moveToPoint(vector2f point, sf::Sprite& sprite, float spd, sf::Time& dT) {
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


void dropEnemyBombs(float* timer, Vector<Invader*>& invaders, sf::Texture& tex) {
	int numType[3] = {};
	int track[3] = {};
	for (int i = 0; i < (invaders.size()); ++i) {
		if (invaders[i]->invType() == 1)
			++numType[0];
		else if (invaders[i]->invType() == 2)
			++numType[1];
		else if (invaders[i]->invType() == 3)
			++numType[2];
	}
	int random[3] = {};
	if (numType[0] > 0)
		random[0] = rand() % numType[0];
	if (numType[1] > 0)
		random[1] = rand() % numType[1];
	if (numType[2] > 0)
		random[2] = rand() % numType[2];
	for (int i = 0; i < invaders.size(); ++i) {

		if (invaders[i]->invType() == 1) {
			if (track[0] == random[0]) {
				if (timer[0] >= 5) {
					invaders[i]->dropBomb(tex);
					timer[0] = 0;
				}
			}
			else
				++track[0];
		}

		else if (invaders[i]->invType() == 2) {
			if (track[1] == random[1]) {
				if (timer[1] >= 3) {
					invaders[i]->dropBomb(tex);
					timer[1] = 0;
				}
			}
			else
				++track[1];
		}

		else if (invaders[i]->invType() == 3) {
			if (track[2] == random[2]) {
				if (timer[2] >= 2) {
					invaders[i]->dropBomb(tex);
					timer[2] = 0;
				}
			}
			else
				++track[2];
		}
	}
}

void generateEnemies(Vector<Invader*>& invaders, sf::Texture* invTex, Level& lvl) {
	if (invaders.size() > 0)
		return;
	if (lvl.sans())
		return;
	int enemyNum = 0;
	if (lvl.getShape() == "rectangle" && lvl.getLevel() < 3)
		enemyNum = 24;
	else if (lvl.getShape() == "triangle" && lvl.getLevel() < 3)
		enemyNum = 28;

	else if (lvl.getShape() == "circle" && lvl.getLevel() < 3)
		enemyNum = 14;
	else if (lvl.getShape() == "diamond" && lvl.getLevel() < 3)
		enemyNum = 20;
	else if (lvl.getShape() == "heart" && lvl.getLevel() < 3)
		enemyNum = 18;

	else if (lvl.getShape() == "cross")
		enemyNum = 21;
	else if (lvl.getShape() == "rectangle" && lvl.getLevel() >= 3)
		enemyNum = 40;
	else if (lvl.getShape() == "triangle" && lvl.getLevel() >= 3)
		enemyNum = 43;
	else if (lvl.getShape() == "circle" && lvl.getLevel() >= 3)
		enemyNum = 24;
	else if (lvl.getShape() == "diamond" && lvl.getLevel() >= 3)
		enemyNum = 33;
	else if (lvl.getShape() == "heart" && lvl.getLevel() >= 3)
		enemyNum = 25;


	int n = 0;
	for (int i = 0; i < enemyNum; ++i) {
		n = rand() % 3;
		if (n == 0) {
			Alpha* temp = new Alpha(invTex[0]);
			invaders.push_back(temp);
		}
		else if (n == 1) {
			Beta* temp = new Beta(invTex[2]);
			invaders.push_back(temp);
		}
		else {
			Gamma* temp = new Gamma(invTex[4]);
			invaders.push_back(temp);
		}
	}
	
}

void arrangeRectangle(Vector<Invader*>& invaders, Level& lvl) {
	if (lvl.changing()) {
		for (int i = 0; i < 4; ++i) {
			invaders[i]->setPos(vector2f(200, i * 80));;
		}
		for (int i = 0; i < 8; ++i) {
			invaders[4 + i]->setPos(vector2f(300 + i * 100, 0));
		}
		for (int i = 0; i < 4; ++i)
			invaders[12 + i]->setPos(vector2f(1100, i * 80));
		for (int i = 0; i < 8; ++i)
			invaders[16 + i]->setPos(vector2f(300 + i * 100, 240));

		if (lvl.getLevel() == 3) {
			for (int i = 0; i < 8; ++i)
				invaders[24 + i]->setPos(vector2f(300 + i * 100, 80));
			for (int i = 0; i < 8; ++i)
				invaders[32 + i]->setPos(vector2f(300 + i * 100, 160));
		}

		lvl.setChange(false);
	}
}

void arrangeTriangle(Vector<Invader*>& invaders, Level& lvl) {
	if (lvl.changing()) {
		for (int i = 0; i < 8; ++i)
			invaders[i]->setPos(vector2f(200 + i * 70, 245 - i * 35));
		for (int i = 0; i < 7; ++i)
			invaders[8 + i]->setPos(vector2f(760 + i * 70, 35 + i * 35));
		for (int i = 0; i < 13; ++i)
			invaders[15 + i]->setPos(vector2f(270 + i * 70, 300));

		if (lvl.getLevel() == 3) {
			for (int i = 0; i < 9; ++i) {
				invaders[28 + i]->setPos(vector2f(410 + i * 70, 210));
			}
			for (int i = 0; i < 5; ++i) {
				invaders[37 + i]->setPos(vector2f(550 + i * 70, 140));
			}
			invaders[42]->setPos(vector2f(690, 70));
		}

		lvl.setChange(false);
	}
}

void arrangeCross(Vector<Invader*>& invaders, Level& lvl) {
	if (lvl.changing()) {
		for (int i = 0; i < 11; ++i)
			invaders[i]->setPos(vector2f(300 + i * 70, 20 + i * 35));
		for (int i = 0; i < 10; ++i) {
			if (i >= 5)
				invaders[11 + i]->setPos(vector2f(930 - i * 70, 40 + i * 35));
			else
				invaders[11 + i]->setPos(vector2f(1000 - i * 70, 20 + i * 35));
		}

		lvl.setChange(false);
	}
}

void arrangeCircle(Vector<Invader*>& invaders, Level& lvl) {
	if (lvl.changing()) {
		invaders[0]->setPos(vector2f(630, 10));
		for (int i = 0; i < 2; ++i)
			invaders[1 + i]->setPos(vector2f(540 + i * 180, 40));
		for (int i = 0; i < 2; ++i)
			invaders[3 + i]->setPos(vector2f(480 + i * 300, 80));
		for (int i = 0; i < 2; ++i)
			invaders[5 + i]->setPos(vector2f(450 + i * 360, 130));
		for (int i = 0; i < 2; ++i)
			invaders[7 + i]->setPos(vector2f(450 + i * 360, 190));
		for (int i = 0; i < 2; ++i)
			invaders[9 + i]->setPos(vector2f(480 + i * 300, 240));
		for (int i = 0; i < 2; ++i)
			invaders[11 + i]->setPos(vector2f(540 + i * 180, 280));
		invaders[13]->setPos(vector2f(630, 310));

		if (lvl.getLevel() == 3) {
			for (int i = 0; i < 4; ++i) {
				invaders[14 + i]->setPos(vector2f(530 + i * 70, 130));
			}
			for (int i = 0; i < 4; ++i)
				invaders[18 + i]->setPos(vector2f(530 + i * 70, 190));
			invaders[22]->setPos(vector2f(635, 70));
			invaders[23]->setPos(vector2f(635, 250));
		}

		lvl.setChange(false);
	}
}

void arrangeDiamond(Vector<Invader*>& invaders, Level& lvl) {
	if (lvl.changing()) {
		for (int i = 0; i < 6; ++i)
			invaders[i]->setPos(vector2f(630 - 60 * i, 10 + i * 30));
		for (int i = 0; i < 5; ++i)
			invaders[6 + i]->setPos(vector2f(390 + 60 * i, 190 + 30 * i));
		for (int i = 0; i < 5; ++i)
			invaders[11 + i]->setPos(vector2f(690 + 60 * i, 280 - 30 * i));
		for (int i = 0; i < 4; ++i)
			invaders[16 + i]->setPos(vector2f(690 + 60 * i, 40 + 30 * i));

		if (lvl.getLevel() == 3) {
			for (int i = 0; i < 7; ++i)
				invaders[20 + i]->setPos(vector2f(450 + 60 * i, 160));
			for (int i = 0; i < 3; ++i)
				invaders[27 + i]->setPos(vector2f(570 + 60 * i, 100));
			for (int i = 0; i < 3; ++i)
				invaders[30 + i]->setPos(vector2f(570 + 60 * i, 220));
		}

		lvl.setChange(false);
	}
}

void arrangeHeart(Vector<Invader*>& invaders, Level& lvl) {
	if (lvl.changing()) {
		for (int i = 0; i < 6; ++i)
			invaders[i]->setPos(vector2f(630 - 45 * i, 280 - 40 * i));
		for (int i = 0; i < 5; ++i)
			invaders[6 + i]->setPos(vector2f(675 + 45 * i, 240 - 40 * i));
		invaders[11]->setPos(vector2f(450, 20));
		invaders[12]->setPos(vector2f(515, 30));
		invaders[13]->setPos(vector2f(580, 40));
		invaders[14]->setPos(vector2f(630, 70));
		invaders[15]->setPos(vector2f(680, 40));
		invaders[16]->setPos(vector2f(745, 30));
		invaders[17]->setPos(vector2f(810, 20));

		if (lvl.getLevel() == 3) {
			for (int i = 0; i < 3; ++i)
				invaders[18 + i]->setPos(vector2f(480 + 60 * i, 70+ 30 * i));
			for (int i = 0; i < 3; ++i)
				invaders[21 + i]->setPos(vector2f(670 + 60 * i, 130 - 30 * i));
			invaders[24]->setPos(vector2f(630, 190));
		}

		lvl.setChange(false);
	}
}

void arrangeShape(Vector<Invader*>& inv, Level& lvl) {
	if (lvl.animating())
		return;

	if (lvl.getShape() == "rectangle")
		arrangeRectangle(inv, lvl);
	else if (lvl.getShape() == "triangle")
		arrangeTriangle(inv, lvl);
	else if (lvl.getShape() == "cross")
		arrangeCross(inv, lvl);
	else if (lvl.getShape() == "circle")
		arrangeCircle(inv, lvl);
	else if (lvl.getShape() == "diamond")
		arrangeDiamond(inv, lvl);
	else if (lvl.getShape() == "heart")
		arrangeHeart(inv, lvl);
}

void incLevelPhase(int invSize, Level& lvl) {
	if (lvl.sans())
		return;
	if (invSize == 0)
		lvl.incPhase();
}

void animateInvaders(Vector<Invader*>& invaders, sf::Sound& ventSound, sf::Time& dT) {

	for (int i = 0; i < invaders.size(); ++i) {
		if (invaders[i]->bombOn())
			invaders[i]->updateBomb(dT);
		invaders[i]->updateVent();
		if (invaders[i]->ventFrame() == 1)
			ventSound.play();
		invaders[i]->updateExplosion();
	}
}

void invaderCollisions(Vector<Invader*>& invaders, sf::RenderWindow& window, sf::Texture* animTex, Player* p) {
	for (int i = 0; i < (invaders.size()); ++i) {
		if (invaders[i]->bombOn())
			if (invaders[i]->playerColBomb(p->sprite, 35, 50) && p->canDie()) {
				p->reduceLife();
				invaders[i]->createVent(animTex[0]);
				invaders[i]->animateVent();
				invaders[i]->deleteBomb();
			}

		if (invaders[i]->bombOffScreen())
			invaders[i]->deleteBomb();

		if (invaders[i]->ventEnded())
			invaders[i]->deleteVent();

		for (int j = 0; j < p->bullets.size(); ++j) {

			if (invaders[i]->collided(p->bullets[j].getSprite(), 24, 10)) {
				invaders[i]->reduceHealth();
				if (invaders[i]->dead()) {
					if (invaders[i]->invType() == 1) {
						invaders[i]->createExplosion(animTex[1]);
						p->incScore(10);
					}
					else if (invaders[i]->invType() == 2) {
						invaders[i]->createExplosion(animTex[2]);
						p->incScore(15);
					}
					else if (invaders[i]->invType() == 3) {
						invaders[i]->createExplosion(animTex[3]);
						p->incScore(20);
					}
					invaders[i]->animateExplosion();
				}
				invaders[i]->move(500, 5000);
				if (!p->fireAddon)
					p->bullets.erase(j);
			}
		}

		if (invaders[i]->collided(p->sprite) && p->blinking == false) {
			if (p->canDie())
				p->reduceLife();
			invaders[i]->reduceHealth();
			if (invaders[i]->dead()) {
				if (invaders[i]->invType() == 1)
					invaders[i]->createExplosion(animTex[1]);
				else if (invaders[i]->invType() == 2)
					invaders[i]->createExplosion(animTex[2]);
				else if (invaders[i]->invType() == 3)
					invaders[i]->createExplosion(animTex[3]);
				invaders[i]->animateExplosion();
			}
			invaders[i]->move(500, 5000);
		}

		if (invaders[i]->dead() && invaders[i]->explosionEnded()) {
			invaders[i]->deleteExplosion();
			if (invaders[i]->ventOn() || invaders[i]->bombOn()) {
				invaders[i]->move(500, 5000);
			}
			else if (invaders[i]->ventEnded() || !invaders[i]->ventOn())
				invaders.erase(i);
		}
	}
}

void enemyCollision(Texture* runTex, Level& lvl, Animation*& runOne, Animation*& runTwo, Texture* explosionTex, Animation*& explode, sf::Time& dT) {

	if (lvl.sans())
		return;

	if (lvl.animating()) {
		if (runOne == nullptr && runTwo == nullptr) {
			runOne = new Animation(0.07, 8, runTex[0]);
			runTwo = new Animation(0.07, 8, runTex[1]);
			runOne->sprite.setScale(0.2, 0.2);
			runTwo->sprite.setScale(0.2, 0.2);
			runOne->animate(vector2f(0, 300));
			runTwo->animate(vector2f(1300, 300));
		}
		runOne->update(true);
		runTwo->update(true);

		moveToPoint(vector2f(650, 300), runOne->sprite, 0.1, dT);
		moveToPoint(vector2f(650, 300), runTwo->sprite, 0.1, dT);

		if (runOne->curFrame > 2 && runOne->sprite.getPosition().x >= runTwo->sprite.getPosition().x) {
			delete runOne;
			delete runTwo;
			runOne = nullptr;
			runTwo = nullptr;
			lvl.setAnim(false);
			lvl.setBomb(true);
		}
	}
	if (lvl.playBomb()) {
		if (explode == nullptr) {
			if (lvl.getShape() == "rectangle") {
				explode = new Animation(0.05, 8, explosionTex[0]);
				explode->sprite.setScale(1.3, 1.3);
				explode->animate(vector2f(620, 300));
			}
			else if (lvl.getShape() == "triangle") {
				explode = new Animation(0.09, 6, explosionTex[1]);
				explode->sprite.setScale(0.8, 0.8);
				explode->animate(vector2f(630, 300));
			}
			else if (lvl.getShape() == "cross") {
				explode = new Animation(0.05, 11, explosionTex[2]);
				explode->sprite.setScale(1.5, 1.5);
				explode->animate(vector2f(600, 300));
			}
			else if (lvl.getShape() == "circle") {
				explode = new Animation(0.05, 14, explosionTex[3]);
				explode->sprite.setScale(1.2, 1.2);
				explode->animate(vector2f(630, 300));
			}
			else if (lvl.getShape() == "diamond") {
				explode = new Animation(0.08, 10, explosionTex[4]);
				explode->sprite.setScale(1.4, 1.4);
				explode->animate(vector2f(620, 300));
			}
			else if (lvl.getShape() == "heart") {
				explode = new Animation(0.06, 8, explosionTex[5]);
				explode->sprite.setScale(0.6, 0.6);
				explode->animate(vector2f(650, 300));
			}
		}
		explode->update();
		if (explode->curFrame == explode->numberOfFrames - 1) {
			delete explode;
			explode = nullptr;
			lvl.setBomb(false);
			lvl.setChange(true);
		}
	}
}

void moveInvaders(Vector<Invader*>& invaders, bool* leftOrRight, Texture* invRun, Texture* baseTex, float* timeAndDelay, int* frames, Level& lvl, sf::Time& dT) {

	// Move every invader to the left in this case
	if (leftOrRight[0] && timeAndDelay[2] >= timeAndDelay[3]) {
		for (int i = 0; i < invaders.size(); ++i) {
			moveToPoint(vector2f(invaders[i]->getPos().x - 50, invaders[i]->getPos().y), invaders[i]->getSprite(), invaders[i]->getSpeed(), dT);
			if (invaders[i]->getPos().x < 50) {
				leftOrRight[0] = false;
				leftOrRight[1] = true;
				timeAndDelay[2] = 0;
			}
			invaders[i]->setRunning(true);
		}

		if (timeAndDelay[0] >= timeAndDelay[1]) {
			for (int i = 0; i < invaders.size(); ++i) {
				if (invaders[i]->invType() == 1)
					invaders[i]->getSprite().setTexture(invRun[1]);
				else if (invaders[i]->invType() == 2)
					invaders[i]->getSprite().setTexture(invRun[3]);
				else
					invaders[i]->getSprite().setTexture(invRun[5]);

				invaders[i]->getSprite().setTextureRect(sf::IntRect(frames[0] * 400, 0, 400, 400));
				invaders[i]->getSprite().setScale(0.17, 0.215);
			}
			timeAndDelay[0] = 0;
			++frames[0];

		}

		if (frames[0] == frames[1] - 1)
			frames[0] = 2;
	}

	// Move every invader to the right
	else if (leftOrRight[1] && timeAndDelay[2] >= timeAndDelay[3]) {
		for (int i = 0; i < invaders.size(); ++i) {
			moveToPoint(vector2f(invaders[i]->getPos().x + 50, invaders[i]->getPos().y), invaders[i]->getSprite(), invaders[i]->getSpeed(), dT);
			if (invaders[i]->getPos().x > 1220) {
				leftOrRight[0] = true;
				leftOrRight[1] = false;
				timeAndDelay[2] = 0;
			}
			invaders[i]->setRunning(true);
		}

		if (timeAndDelay[0] >= timeAndDelay[1]) {
			for (int i = 0; i < invaders.size(); ++i) {
				if (invaders[i]->invType() == 1)
					invaders[i]->getSprite().setTexture(invRun[0]);
				else if (invaders[i]->invType() == 2)
					invaders[i]->getSprite().setTexture(invRun[2]);
				else
					invaders[i]->getSprite().setTexture(invRun[4]);

				invaders[i]->getSprite().setTextureRect(sf::IntRect(frames[0] * 400, 0, 400, 400));
				invaders[i]->getSprite().setScale(0.17, 0.215);
			}
			timeAndDelay[0] = 0;
			++frames[0];
		}
		if (frames[0] == frames[1] - 1)
			frames[0] = 2;
	}
	else if (timeAndDelay[2] < timeAndDelay[3]) {
		for (int i = 0; i < invaders.size(); ++i) {
			if (invaders[i]->invType() == 1 && leftOrRight[1])
				invaders[i]->getSprite().setTexture(baseTex[0]);
			else if (invaders[i]->invType() == 1 && leftOrRight[0])
				invaders[i]->getSprite().setTexture(baseTex[1]);

			else if (invaders[i]->invType() == 2 && leftOrRight[1])
				invaders[i]->getSprite().setTexture(baseTex[2]);
			else if (invaders[i]->invType() == 2 && leftOrRight[0])
				invaders[i]->getSprite().setTexture(baseTex[3]);

			else if (invaders[i]->invType() == 3 && leftOrRight[1])
				invaders[i]->getSprite().setTexture(baseTex[4]);
			else if (invaders[i]->invType() == 3 && leftOrRight[0])
				invaders[i]->getSprite().setTexture(baseTex[5]);

			invaders[i]->getSprite().setTextureRect(sf::IntRect(0, 0, 68, 86));
			invaders[i]->getSprite().setScale(1, 1);
			invaders[i]->setRunning(false);
		}
	}

	int n = (lvl.shapeNum() - invaders.size()) / 6;

	for (int i = 0; i < invaders.size(); ++i) {
		if (lvl.getLevel() == 1)
			invaders[i]->setSpeed(0.01 + 0.008 * n);
		else if (lvl.getLevel() == 2)
			invaders[i]->setSpeed(0.01 + 0.013 * n);
		else
			invaders[i]->setSpeed(0.01 + 0.018 * n);
	}

	if (lvl.getLevel() == 1)
		timeAndDelay[3] = 2;
	else if (lvl.getLevel() == 2)
		timeAndDelay[3] = 1;
	else if (lvl.getLevel() == 3)
		timeAndDelay[3] = 0.5;

	timeAndDelay[1] = 0.2 - (n * 0.02);

}

void createSans(Level& lvl, Vector<Enemy *>&bosses) {
	if (lvl.sans()) {
		if (bosses.size() == 0) {
			Sans * temp = new Sans;
			bosses.push_back(temp);

		}
	}
}

void changeSansHead(sf::Sprite& sprite, sf::Texture* tex, float& timer, bool sansLv) {
	if (sansLv) {
		sprite.setTexture(tex[badTime]);
		return;
	}
	else if (timer >= 30) {
		int n = rand() % 3;
		if (n == 0)
			sprite.setTexture(tex[lookingRight]);
		else if (n == 1)
			sprite.setTexture(tex[normal]);
		else if (n == 2)
			sprite.setTexture(tex[wink]);
		timer = 0;
	}
}

void breakHeart(Animation*& heartBreak, sf::Texture& tex, bool& breaking, sf::Sprite * hearts, int curLives) {
	if (breaking) {
		breaking = false;

		heartBreak = new Animation(0.07, 41, tex, true);
		heartBreak->sprite.setScale(0.6, 0.6);
		heartBreak->animate(vector2f(hearts[curLives].getPosition().x, hearts[curLives].getPosition().y));
		heartBreak->curFrame = 1;
	}
}

void animateHeart(Animation*& heartBreak, sf::Sound& heartSound) {
	if (heartBreak != nullptr) {
		if (heartBreak->curFrame == heartBreak->numberOfFrames - 1) {
			delete heartBreak;
			heartBreak = nullptr;
			return;
		}
		else {
			if (heartBreak->curFrame == 1) {
				heartSound.play();
			}
			heartBreak->update();
		}
	}
}