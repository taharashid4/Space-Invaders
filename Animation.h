#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "vector2f.h"
#include <time.h>

class Animation {
public:
    float animationDelay;
    sf::Sprite sprite;
    sf::Texture spriteSheet;
    vector2f storePos;
    int numberOfFrames, frameWidth, frameHeight, curFrame;
    bool animStart, squareSheet;
    float timer;
    int imgPerRow;

public:
    Animation();

    Animation(float delay, int frameNum);

    void setSheet(sf::Texture& tex, bool square = 0);

    Animation(float delay, int frameNum, sf::Texture& sheet, bool square = 0);

    // sprite.setTextureRect(sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));

    void animate(vector2f);

    void update(bool reset = false);

    void draw(sf::RenderWindow& window) { window.draw(sprite); }
};