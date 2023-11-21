#pragma once
#include "Enemy.h"
#include "Player.h"
#include "GasterBlaster.h"
#include "Animation.h"
#include <queue>

using namespace sf;

class Sans: public Enemy {

	sf::Sprite swapHeadBody[2];
    sf::Sprite idleHeadBody;
    sf::Sprite legs;
    sf::Sprite sansSweat;
    sf::Sprite deathSprite;

    Texture sansHead;
    Texture sansBody;
    Texture sansLegs, idleTex, boneTex, deathTex, sweatTex;
    Texture gasterTex;

    Vector<GasterBlaster> gasters;
    Vector<sf::Sprite> bones;

    
    
    vector2f storePos, gasterPos;

    sf::Sound gasterSound;
    sf::SoundBuffer gasterBuffers[10];

    sf::Sound gasterSounds[10];

    int idleFrame;
    float idleTimer, idleDelay;
    
    bool idle, moveRight, moveLeft, hitBullet;
    bool wobble[2];

    int fightPhase, track;
    float phaseTimer[5];
    bool phaseSteps[10];

public:

    Sans();

	void draw(sf::RenderWindow& window);

	virtual bool collided(sf::Sprite other, int xOffset = 0, int yOffset = 0) override;

    virtual int sansOrMonster() { return 1; }

    void animateSans(float& time);

    void phaseOne(float& timer, Player *, sf::Time&);

    void phaseTwo(float& timer, sf::Time&);

    void phaseThree(float& timer, Player*, sf::Time&);

    void phaseFour(float& timer, sf::Time&);

    void phaseFive(float& timer, sf::RenderWindow& window, Player *, sf::Time&);

    void phaseSix(float& timer, sf::RenderWindow& window, Player *, sf::Time&);

    void phaseSeven(float& timer, sf::RenderWindow& window, Player *, sf::Time&);

    void phaseEight(float& timer, sf::RenderWindow& window, Player*, sf::Time&);

    void phaseNine(float& timer, Player*, sf::Time&);

    void dodgeSans(sf::Sprite& other, float& time, sf::Time&);

    void incPhase();

    void deleteGasters();

    bool gasterCollision(sf::Sprite& other);

    bool boneCollision(sf::Sprite& other);

    void deleteBones(int index);

    int curPhase() const { return fightPhase; }

    int vertPos() { return legs.getPosition().y + 30; }

    void activateHit() { hitBullet = true; }
    
    void playSounds();
};

