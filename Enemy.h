#pragma once
#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "Projectile.h"
#include "vector2f.h"
#include "Animation.h"

class Enemy {
protected:
	sf::Sprite sprite;
	vector2f pos;
	int m_health;
	float fireInterval;
	float speed;

public:

	Enemy();
	Enemy(const sf::Texture& tex, int health, float interval);

	int health() const { return m_health; }

	bool dead() { return m_health <= 0; }

	virtual void draw(sf::RenderWindow& window) { window.draw(sprite); }

	vector2f getPos() {
		pos.x = sprite.getPosition().x;
		pos.y = sprite.getPosition().y;
		return pos;
	}

	void reduceHealth() { m_health -= 10; }

	void setPos(vector2f pos) { sprite.setPosition(pos.x, pos.y); }

	void move(vector2f vec) { sprite.setPosition(vec.x, vec.y); }

	void move(float x, float y) { sprite.setPosition(x, y); }

	float getSpeed() const { return speed; }
	void setSpeed(float n) { speed = n; }

	virtual int sansOrMonster() { return 0; }

	sf::Sprite& getSprite() { return sprite; }

	virtual bool collided(sf::Sprite other, int xOffset = 0, int yOffset = 0) = 0;

	virtual ~Enemy() = default;
};

class Invader : virtual public Enemy {
public:
	Bomb* bomb;
	Animation* venting;
	Animation* explosionAnim;
	bool running;

public:
	Invader() {
		explosionAnim = nullptr;
		bomb = nullptr;
		venting = nullptr;
		running = false;
	}

	bool bombOn() { return (bomb != nullptr); }
	void dropBomb(sf::Texture& tex);
	void drawBomb(sf::RenderWindow& window) { if (bomb != nullptr) bomb->draw(window); }
	bool bombOffScreen();
	void updateBomb(sf::Time& dT) { if (bomb != nullptr) bomb->updateProjectile(dT); }
	void deleteBomb();

	void createVent(sf::Texture& tex);
	int ventFrame() { if (venting) return venting->curFrame; }
	void updateVent() { if (venting != nullptr) venting->update(); };
	bool ventEnded();
	void drawVent(sf::RenderWindow& window) { if (ventOn()) venting->draw(window); }
	bool ventOn() { return (venting != nullptr); }
	void animateVent();
	void deleteVent();
	void incVentTimer(float time) { if (ventOn()) venting->timer += time; }

	void createExplosion(sf::Texture& tex);
	void updateExplosion() { if (explosionAnim != nullptr) explosionAnim->update(); }
	void animateExplosion();
	bool explosionEnded();
	void drawExplosion(sf::RenderWindow& window) { if (explosionAnim != nullptr) explosionAnim->draw(window); }
	void deleteExplosion();
	void incExplosionTimer(float time) { if (explosionAnim != nullptr) explosionAnim->timer += time; }

	virtual int invType() const = 0;

	bool getRunning() const { return running; }
	void setRunning(bool n) { running = n; }

	bool playerColBomb(sf::Sprite& sprite, int xOffset = 0, int yOffset = 0);

	bool collided(sf::Sprite other, int xOffset = 0, int yOffset = 0) override;

	float& ventTimer() { return venting->timer; }

	~Invader() {
		if (explosionAnim)
			delete explosionAnim;
		if (bomb)
			delete bomb;
		if (venting)
			delete venting;
	}

};

class Alpha : public Invader {
public:
	Alpha(const sf::Texture& tex) :Enemy(tex, 10, 5) {}
	
	virtual int invType() const { return 1; }

	~Alpha() {}
};

class Beta : public Invader {
public:
	Beta(const sf::Texture& tex) :Enemy(tex, 10, 3) {}

	virtual int invType() const { return 2; }

	~Beta() {}
};

class Gamma : public Invader {
public:
	Gamma(const sf::Texture& tex) :Enemy(tex, 10, 2) {}

	virtual int invType() const { return 3; }

	~Gamma() {}
};