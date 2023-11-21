#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Vector.h"
#include "vector2f.h"

class Projectile {
protected:
    sf::Sprite sprite;
    float speed;
    bool textured;

public:
    Projectile();
    Projectile(const sf::Texture& tex, vector2f& location, float spd);

    void draw(sf::RenderWindow& window) { window.draw(sprite); }

    sf::Sprite& getSprite() { return sprite; }

    vector2f getPos() { return vector2f(sprite.getPosition().x, sprite.getPosition().y); }

    bool collided(const sf::Sprite& other, int xOffset = 0, int yOffset = 0);

    void setPos(vector2f vec) { sprite.setPosition(vec.x, vec.y); }

    void setSpeed(float spd) { speed = spd; }

    void setTextured(bool t) { textured = t; }

    virtual bool leftScreen() = 0;

    virtual void updateProjectile(sf::Time&) = 0;

    virtual ~Projectile() = default;
};

class Bullet : public Projectile {
    float angle;
public:

    Bullet() { angle = 90; }
    Bullet(const sf::Texture& tex, vector2f shipLocation, float ang = 90) :Projectile(tex, shipLocation, 0.2) {
        textured = true;
        angle = ang;
    }

    Bullet& operator=(const sf::Texture& tex);


    virtual bool leftScreen() override;

    virtual void updateProjectile(sf::Time&) override;
};

class Bomb : public Projectile {
public:
    Bomb() {}
    Bomb(const sf::Texture& tex, vector2f loc) :Projectile(tex, loc, 0.1) {
        textured = true;
    }

    Bomb& operator=(const sf::Texture& tex);

    virtual bool leftScreen() override;

    virtual void updateProjectile(sf::Time&) override;

    ~Bomb() {}
};