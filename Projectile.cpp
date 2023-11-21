#include "Projectile.h"

Projectile::Projectile() {
    speed = 0;
    textured = 0;
    sprite.setPosition(5000, 5000);
}

Projectile::Projectile(const sf::Texture& tex, vector2f& location, float spd) {
    sprite.setTexture(tex);
    sprite.setPosition(location.x, location.y);
    speed = spd;
    textured = false;
}

bool Projectile::collided(const sf::Sprite& other, int xOffset, int yOffset) {
    if (textured) {
        if ((sprite.getPosition().x + sprite.getTextureRect().width - xOffset >= other.getPosition().x
            && sprite.getPosition().y + sprite.getTextureRect().height - yOffset >= other.getPosition().y)
            && (sprite.getPosition().x + xOffset <= other.getPosition().x + other.getTextureRect().width
                && sprite.getPosition().y + yOffset <= other.getPosition().y + other.getTextureRect().height ))
            return 1;
    }
    return 0;
}

Bullet& Bullet::operator=(const sf::Texture& tex) {
    sprite.setTexture(tex);
    textured = true;
    return *this;
}

bool Bullet::leftScreen() {
    // The only way for a bullet to leave the screen is vertically, when it's y position goes above the screen
    if (sprite.getPosition().y < -20)
        return 1;
    else if (sprite.getPosition().x < -30)
        return 1;
    else if (sprite.getPosition().x > 1390)
        return 1;
    return 0;
}

void Bullet::updateProjectile(sf::Time& dT) {
    float moveX = cos(angle * 3.141592 / 180);
    float moveY = -sin(angle * 3.141592 / 180);
    moveY *= speed;
    moveX *= speed;
    sprite.move(moveX * dT.asSeconds() * 5000, moveY * dT.asSeconds() * 5000);
}

Bomb& Bomb::operator=(const sf::Texture& tex) {
    sprite.setTexture(tex);
    textured = true;
    return *this;
}

bool Bomb::leftScreen() {
    if (sprite.getPosition().y >= 768)
        return 1;
    return 0;
}

void Bomb::updateProjectile(sf::Time& dT) {
    float moveY = 1;
    moveY *= speed;

    sprite.move(0, moveY * dT.asSeconds() * 5000);
}