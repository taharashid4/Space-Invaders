#include "Animation.h"

Animation::Animation() {
    animationDelay = 0;
    numberOfFrames = 0;
    animStart = 0;
    curFrame = 0;
    squareSheet = 0;
    frameWidth = 0;
    frameHeight = 0;
    timer = 0;
    storePos.x = 0;
    storePos.y = 0;
    imgPerRow = 0;
}

Animation::Animation(float delay, int frameNum) {
    animationDelay = delay;
    numberOfFrames = frameNum;
    animStart = 0;
    curFrame = 0;
    squareSheet = 0;
    frameWidth = 0;
    frameHeight = 0;
    timer = 0;
    storePos.x = 0;
    storePos.y = 0;
    imgPerRow = 0;
}

void Animation::setSheet(sf::Texture& tex, bool square) {
    spriteSheet = tex;
    squareSheet = square;
    frameWidth = spriteSheet.getSize().x / numberOfFrames;
    frameHeight = spriteSheet.getSize().y;
    if (squareSheet) {
        float x = sqrt(numberOfFrames);
        imgPerRow = floor(x);
        frameWidth *= imgPerRow;
        frameHeight /= imgPerRow;
    }

    sprite.setTexture(tex, true);
    sprite.setPosition(5000, 5000);
    animStart = 0;
    curFrame = 0;
    timer = 0;
    storePos.x = 0;
    storePos.y = 0;
}

Animation::Animation(float delay, int frameNum, sf::Texture& sheet, bool square) {
    animationDelay = delay;
    numberOfFrames = frameNum;
    spriteSheet = sheet;
    squareSheet = square;
    frameWidth = spriteSheet.getSize().x / numberOfFrames;
    frameHeight = spriteSheet.getSize().y;

    if (squareSheet) {
        float x = sqrt(numberOfFrames);
            
        imgPerRow = floor(x);
        frameWidth = spriteSheet.getSize().x;
        frameWidth /= imgPerRow;
        frameHeight /= imgPerRow;
        int temp = sqrt(numberOfFrames);
        if (x != temp) {
            frameHeight = spriteSheet.getSize().y;
            frameHeight /= (imgPerRow + 1);
        }
    }

    sprite.setTexture(sheet, true);
    sprite.setPosition(5000, 5000);
    animStart = 0;
    curFrame = 0;
    timer = 0;
}

void Animation::animate(vector2f pos) {
    if (animStart == 0) {
        animStart = 1;
        storePos = pos;
        curFrame = 0;
    }
}


void Animation::update(bool replay) {
    if (animStart) {
        if (curFrame == 1)
            sprite.setPosition(storePos.x, storePos.y);
        
        if (timer >= animationDelay) {
            if (squareSheet == false || curFrame < imgPerRow) {
                sprite.setTextureRect(sf::IntRect(curFrame * frameWidth, 0, frameWidth, frameHeight));
                timer = 0;
                ++curFrame;
            }
            else if (curFrame >= imgPerRow) {
                int topLeft = curFrame % imgPerRow;
                int top = curFrame / imgPerRow;
                sprite.setTextureRect(sf::IntRect(topLeft * frameWidth, top * frameHeight, frameWidth, frameHeight));
                timer = 0;
                ++curFrame;
            }
        }
        if (curFrame == numberOfFrames - 1) {
            if (replay) {
                curFrame = 2;
            }
            else {
                animStart = 0;
                sprite.setPosition(5000, 5000);
            }
        }
    }
}