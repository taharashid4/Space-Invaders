#include "Enemy.h"

Enemy::Enemy() {
	m_health = 0;
	fireInterval = 0;
	sprite.setPosition(5000, 5000);
	speed = 0.01;
}

Enemy::Enemy(const sf::Texture& tex, int health, float interval) {
	m_health = health;
	fireInterval = interval;
	sprite.setTexture(tex);
	sprite.setPosition(5000, 5000);
	speed = 0.01;
}

void Invader::dropBomb(sf::Texture& tex) {
	if (m_health > 0) {
		bomb = new Bomb(tex, vector2f(sprite.getPosition().x + 57, sprite.getPosition().y));
		bomb->getSprite().setScale(0.8, 0.8);
	}
}

void Invader::deleteBomb() {
	delete bomb;
	bomb = nullptr;
}

bool Invader::playerColBomb(sf::Sprite& sprite, int xOffset, int yOffset) {
	return bomb->collided(sprite, xOffset, yOffset);
}

void Invader::deleteVent()
{
	delete venting;
	venting = nullptr;
}

void Invader::animateExplosion()
{
	if (invType() == 1)
		explosionAnim->animate(vector2f(getPos().x + 15, getPos().y + 20));
	else if (invType() == 2)
		explosionAnim->animate(vector2f(getPos().x - 5, getPos().y - 5));
	else if (invType() == 3)
		explosionAnim->animate(vector2f(getPos().x, getPos().y - 20));

}

bool Invader::ventEnded() {
	if (venting == nullptr)
		return 0;
	return venting->curFrame == venting->numberOfFrames - 1;
}

void Invader::deleteExplosion()
{
	delete explosionAnim;
	explosionAnim = nullptr;
}

bool Invader::bombOffScreen()
{
	if (bomb != nullptr)
		return bomb->leftScreen();
	return false;
}

void Invader::createVent(sf::Texture& tex)
{
	if (venting != nullptr)
		return;
	venting = new Animation(0.12, 9, tex);
	venting->sprite.setScale(0.72, 0.72);
}

void Invader::createExplosion(sf::Texture& tex)
{
	if (explosionAnim != nullptr)
		return;
	if (invType() == 1) {
		explosionAnim = new Animation(0.05, 6, tex);
		explosionAnim->sprite.setScale(0.16, 0.16);
	}
	else if (invType() == 2) {
		explosionAnim = new Animation(0.03, 25, tex, true);
		explosionAnim->sprite.setScale(0.3, 0.3);
	}
	else if (invType() == 3) {
		explosionAnim = new Animation(0.05, 9, tex);
		explosionAnim->sprite.setScale(0.25, 0.25);
	}
}

bool Invader::explosionEnded() {
	if (explosionAnim != nullptr) return (explosionAnim->curFrame == explosionAnim->numberOfFrames - 1);
	else
		return true;
}

bool Invader::collided(sf::Sprite other, int xOffset, int yOffset) {
	if (m_health <= 0)
		return 0;
	if (!running) {
		if ((sprite.getPosition().x + sprite.getTexture()->getSize().x - xOffset >= other.getGlobalBounds().left
			&& sprite.getPosition().y + sprite.getTexture()->getSize().y - yOffset >= other.getGlobalBounds().top)
			&& (sprite.getPosition().x + xOffset <= other.getGlobalBounds().left + other.getGlobalBounds().width
				&& sprite.getPosition().y + yOffset <= other.getGlobalBounds().top + other.getGlobalBounds().height))
			return 1;
		else
			return 0;
	}
	else if (running) {
		if ((sprite.getPosition().x + 50 >= other.getGlobalBounds().left
			&& sprite.getPosition().y + 70 >= other.getGlobalBounds().top)
			&& (sprite.getPosition().x + 20 <= other.getGlobalBounds().left + other.getGlobalBounds().width
				&& sprite.getPosition().y + 20 <= other.getGlobalBounds().top + other.getGlobalBounds().height))
			return 1;
		else
			return 0;
	}
}

void Invader::animateVent() {
	if (venting != nullptr) venting->animate(bomb->getPos());
}
