#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "player.h"
#include "Vector.h"
#include "Enemy.h"
#include "Sans.h"
#include "Helper.h"
#include "Animation.h"
#include "Level.h"
#include "Menu.h"
#include "AddOn.h"
#include <fstream>


const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{
public:

    Sprite background; 
    Sprite scoreBox, lifeBox;
    Sprite sansHead;

    Sprite hearts[3];
    Texture heartTex;
    Animation* heartBreak;
    Texture heartBreakSheet;

    Texture mainMenuSheet;

    Texture scoreTex, lifeTex;
    
    Texture sansDialogue[HEAD_NUM];

    Texture bg_textures[4];
    Player *p; 
    Clock clock;
    Clock deltaClock;
    sf::Clock menuClock;

    Music megalovania;

    Music mainThemes[THEME_NUM];

    Menu menu;

    Vector<Invader*> invaders;
    sf::Texture invaderTex[6];
    Texture invaderAnims[5];
    Texture bombTex[3];
    Level level;

    Texture runTex[2];
    Texture runExplosion[6];

    Texture invaderRun[6];

    Texture addonTex[4];

    Vector<Enemy*> bosses;

    Vector<AddOn*> drops;

    int n = 0;

    Sound ventSound;
    SoundBuffer ventBuf;

    Sound heartSound;
    SoundBuffer heartBuffer;
    

    Game()
    {
		p = new Player("img/rotationsprites/amogusship/sheet.png");
		bg_textures[0].loadFromFile("img/background1.jpg");
        bg_textures[1].loadFromFile("img/background2.jpg");
        bg_textures[2].loadFromFile("img/background3.png");
        bg_textures[3].loadFromFile("img/background4.png");
        for (int i = 0; i < 4; ++i)
            bg_textures[i].setRepeated(true);
		background.setTexture(bg_textures[0]);

		scoreTex.loadFromFile("img/textbox.png");
		scoreBox.setTexture(scoreTex); 
        lifeTex.loadFromFile("img/textbox.png");
        lifeBox.setTexture(lifeTex);

        sansDialogue[badTime].loadFromFile("img/sans/faces/bad-o-clock.png");
		sansDialogue[lookingRight].loadFromFile("img/sans/faces/lookright.png");
		sansDialogue[normal].loadFromFile("img/sans/faces/normal.png");
		sansDialogue[wink].loadFromFile("img/sans/faces/wink.png");

        sansHead.setTexture(sansDialogue[normal]);

		scoreBox.setScale(0.475, 0.6);
		scoreBox.setPosition(0, 665);
        sansHead.setScale(0.85, 0.85);
        sansHead.setPosition(20, 685);

        mainMenuSheet.loadFromFile("img/animation/menubackground.png");

        lifeBox.setScale(0.25, 0.4);
        lifeBox.setPosition(1215, 705);

        heartBreak = nullptr;
        heartTex.loadFromFile("img/SOUL.png");
        for (int i = 0; i < 3; ++i) {
            hearts[i].setTexture(heartTex);
            hearts[i].setScale(0.6, 0.6);
            hearts[i].setPosition(1089 + (i * 50), 592);
        }
        heartBreakSheet.loadFromFile("img/animation/heartAnim.png");

		invaderTex[0].loadFromFile("img/invadersprites/alpha.png");
		invaderTex[1].loadFromFile("img/invadersprites/alphaFlip.png");
        invaderTex[2].loadFromFile("img/invadersprites/beta.png");
        invaderTex[3].loadFromFile("img/invadersprites/betaFlip.png");
        invaderTex[4].loadFromFile("img/invadersprites/gamma.png");
        invaderTex[5].loadFromFile("img/invadersprites/gammaFlip.png");

        invaderRun[0].loadFromFile("img/invadersprites/alphaRunRight.png");
        invaderRun[1].loadFromFile("img/invadersprites/alphaRunLeft.png");
        invaderRun[2].loadFromFile("img/invadersprites/betaRunRight.png");
        invaderRun[3].loadFromFile("img/invadersprites/betaRunLeft.png");
        invaderRun[4].loadFromFile("img/invadersprites/gammaRunRight.png");
        invaderRun[5].loadFromFile("img/invadersprites/gammaRunLeft.png");

        bombTex[0].loadFromFile("img/vent.png");

        invaderAnims[0].loadFromFile("img/animation/ventsheet.png");
        invaderAnims[1].loadFromFile("img/animation/bloodsheet.png");
        invaderAnims[2].loadFromFile("img/animation/smokesheet.png");
        invaderAnims[3].loadFromFile("img/animation/firesheet.png");

       

        runTex[0].loadFromFile("img/animation/runningOne.png");
        runTex[1].loadFromFile("img/animation/runningTwo.png");

        runExplosion[0].loadFromFile("img/animation/rectangle.png");
        runExplosion[1].loadFromFile("img/animation/triangle.png");
        runExplosion[2].loadFromFile("img/animation/cross.png");
        runExplosion[3].loadFromFile("img/animation/circle.png");
        runExplosion[4].loadFromFile("img/animation/diamond.png");
        runExplosion[5].loadFromFile("img/animation/heart.png");

        addonTex[0].loadFromFile("img/addOn/asteroid.png");
        addonTex[1].loadFromFile("img/addOn/star.png");
        addonTex[2].loadFromFile("img/addOn/flower.png");
        addonTex[3].loadFromFile("img/addOn/heart.png");

        if (!megalovania.openFromFile("sounds/megalovania.ogg")) {
            cout << "Could not open megalovania.\n";
            exit(10);
        }

        mainThemes[core].openFromFile("sounds/CORE.ogg");
        mainThemes[asgore].openFromFile("sounds/asgore.ogg");
        mainThemes[glamour].openFromFile("sounds/glamour.ogg");
        mainThemes[jevil].openFromFile("sounds/jevil.ogg");
        mainThemes[queen].openFromFile("sounds/queen.ogg");


        if (!heartBuffer.loadFromFile("sounds/heartBreak.ogg"))
            std::cout << "you're heartless :(\n";
        heartSound.setBuffer(heartBuffer);
            
        if (!ventBuf.loadFromFile("sounds/vent.ogg"))
            cout << "ERROR LOADING SOUND\n";
        ventSound.setBuffer(ventBuf);
    }

    void start_game()
    {
        srand(time(0));
        RenderWindow window(VideoMode(1366, 768), title);
        float invaderTimer[3] = {};
        float headTimer = 0;

        bool leftOrRight[2] = {1, 0};
        float runTimerDelay[4] = { 0, 0.2, 2, 2 };
        int curFrameNumFrame[2] = { 1, 8 };
        float pauseTime = 0;
        float bgY = 0;

        int chosenMusic = 0, chosenBg = 0;

        Animation* runOne = nullptr, * runTwo = nullptr, * runExplode = nullptr;
       
        while (window.isOpen())
        {
            float menuTime = menuClock.restart().asSeconds();

            for (int i = 0; i < THEME_NUM; ++i) {
                if (i != chosenMusic && mainThemes[i].getStatus() == sf::Music::Playing)
                    mainThemes[i].stop();
                else if (i == chosenMusic && mainThemes[i].getStatus() != sf::Music::Playing)
                    mainThemes[i].play();
            }

            if (menu.showMain()) {
                menu.displayMain(window, mainMenuSheet, menuTime);
            }

            if (menu.showScore()) {
                menu.displayScore(window, mainMenuSheet, menuTime);
            }
            
            if (menu.showHelp()) {
                menu.displayInst(window, mainMenuSheet, menuTime);
            }

            if (menu.showOptions()) {
                menu.displayOptions(window, background, bg_textures, menuTime, mainThemes, chosenMusic, chosenBg);
            }

            while (menu.showPause()) {
                menu.displayPause(window, mainMenuSheet, menuTime, pauseTime);
                clock.restart();
                deltaClock.restart();
            }
            char temp = '\0';
            while (menu.isGameOver()) {
                menu.showGameOver(window, mainMenuSheet, menuTime, p->m_score, temp);
            }

            if (menu.restart()) {
                p->m_lives = 3;
                p->m_score = 0;
                menu.setRestart(false);
                float invaderTimer[3] = {};
                float headTimer = 0;
                int temp = invaders.size();
                for (int i = temp - 1; i >= 0; --i) {
                    delete invaders[i];
                    invaders.erase(i);
                }
                temp = bosses.size();
                for (int i = temp - 1; i >= 0; --i) {
                    delete bosses[i];
                    bosses.erase(i);
                }
                temp = drops.size();
                for (int i = temp - 1; i >= 0; --i) {
                    delete drops[i];
                    drops.erase(i);
                }
                delete heartBreak;
                heartBreak = nullptr;

                bool leftOrRight[2] = { 1, 0 };
                float runTimerDelay[4] = { 0, 0.2, 2, 2 };
                int curFrameNumFrame[2] = { 1, 8 };
                delete p;
                p = new Player("img/rotationsprites/amogusship/sheet.png");
                
                level.reset();
            }

            if (menu.playGame()) {

                Event e;
                while (window.pollEvent(e))
                {
                    if (e.type == Event::Closed) // If cross/close is clicked/pressed
                        window.close();          // close the game

                    if (e.key.code == sf::Keyboard::Escape) {
                        menu.pauseGame();
                    }
                }

                // Game logic begins here

                float time = clock.getElapsedTime().asSeconds();
                
                clock.restart();
                Time deltaTime = deltaClock.restart();

                for (int i = 0; i < invaders.size(); ++i) {
                    invaders[i]->incVentTimer(time);
                    invaders[i]->incExplosionTimer(time);
                }
                runTimerDelay[0] += time;
                runTimerDelay[2] += time;
                headTimer += time;

                if (heartBreak != nullptr)
                    heartBreak->timer += time;

                if (p->powerUpAddon)
                    p->powerUpTimer += time;
                if (p->fireAddon)
                    p->fireAddonTimer += time;

                p->dropTimer += time;

                if (runOne != nullptr)
                    runOne->timer += time;
                if (runTwo != nullptr)
                    runTwo->timer += time;
                if (runExplode != nullptr)
                    runExplode->timer += time;
                
                for (int i = 0; i < 3; ++i)
                    invaderTimer[i] += time;
                
                p->rotateDelay += time;
                p->fireTimer += time;

                if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) { // If left key is pressed
                    p->move("l", deltaTime);
                    p->moveLeft = true;// Player will move to left
                }
                else
                    p->moveLeft = false;
                if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) { // If right key is pressed
                    p->move("r", deltaTime);// player will move to right
                    p->moveRight = true;
                }
                else
                    p->moveRight = false;
                if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {  // If up key is pressed
                    p->move("u", deltaTime);// playet will move upwards
                    p->moveTop = true;
                }
                else
                    p->moveTop = false;
                if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) { // If down key is pressed
                    p->move("d", deltaTime);
                    p->moveDown = true;
                }
                else
                    p->moveDown = false;
                if (Keyboard::isKeyPressed(Keyboard::Space))
                    p->fire = true;
                ////////////////////////////////////////////////

                p->fireBullet();
                p->controlBullet(deltaTime);
                p->wrapAround();

                enemyCollision(runTex, level, runOne, runTwo, runExplosion, runExplode, deltaTime);

                incLevelPhase(invaders.size(), level);
                generateEnemies(invaders, invaderTex, level);
                dropEnemyBombs(invaderTimer, invaders, bombTex[0]);
                arrangeShape(invaders, level);
                animateInvaders(invaders, ventSound, deltaTime);
                invaderCollisions(invaders, window, invaderAnims, p);
                moveInvaders(invaders, leftOrRight, invaderRun, invaderTex, runTimerDelay, curFrameNumFrame, level, deltaTime);

                changeSansHead(sansHead, sansDialogue, headTimer, level.sans());

                breakHeart(heartBreak, heartBreakSheet, p->breaking, hearts, p->m_lives);
                animateHeart(heartBreak, heartSound);

                if (p->m_lives <= 0) {
                    menu.setGameOver(true);
                    menu.setStartGame(false);
                }

                p->dropAddons(addonTex);
                p->moveDrops(drops, deltaTime);
                p->timeAddons();
              
              

                // Sans is the dragon :)

                createSans(level, bosses);
                bool tmp = false;
                if (level.sans()) {
                    for (int i = 0; i < 5; ++i) {
                        if (mainThemes[i].getStatus() == sf::Music::Playing)
                            mainThemes[i].stop();
                    }
                    if (megalovania.getStatus() != Music::Playing)
                        megalovania.play();
                    dynamic_cast<Sans*>(bosses[0])->animateSans(time);
                    dynamic_cast<Sans*>(bosses[0])->phaseOne(time, p, deltaTime);
                    dynamic_cast<Sans*>(bosses[0])->phaseTwo(time, deltaTime);
                    dynamic_cast<Sans*>(bosses[0])->phaseThree(time, p, deltaTime);
                    dynamic_cast<Sans*>(bosses[0])->phaseFour(time, deltaTime);
                    dynamic_cast<Sans*>(bosses[0])->phaseNine(time, p, deltaTime);
                    for (int i = 0; i < p->bullets.size(); ++i) {
                        dynamic_cast<Sans*>(bosses[0])->dodgeSans(p->bullets[i].getSprite(), time, deltaTime);
                        if (dynamic_cast<Sans*>(bosses[0])->curPhase() == 9 && p->bullets[i].getPos().y <= dynamic_cast<Sans*>(bosses[0])->vertPos()) {
                            p->bullets.erase(i);
                            dynamic_cast<Sans*>(bosses[0])->activateHit();
                        }
                    }
                    dynamic_cast<Sans*>(bosses[0])->playSounds();

                    if (dynamic_cast<Sans*>(bosses[0])->gasterCollision(p->sprite))
                        if (p->canDie()) p->reduceLife();

                    if (dynamic_cast<Sans*>(bosses[0])->boneCollision(p->sprite))
                        if (p->canDie()) p->reduceLife();

                    if (dynamic_cast<Sans*>(bosses[0])->dead() && dynamic_cast<Sans*>(bosses[0])->curPhase() == 10) {
                        delete bosses[0];
                        bosses.erase(0);
                        p->incScore(1000);
                        level.incPhase();
                    }
                }

                if (!level.sans() && megalovania.getStatus() == Music::Playing)
                    megalovania.stop();

                //////////////////////////////////////////////

                window.clear(Color::Black);
                bgY += deltaTime.asSeconds() * 100;
                background.setTextureRect(sf::IntRect(0, 0 - bgY, 1366, 768));
                window.draw(background);    
                window.draw(scoreBox);
                window.draw(sansHead);
                window.draw(lifeBox);
                level.draw(window);
                p->drawScore(window);
                for (int i = 0; i < p->m_lives; ++i)
                    window.draw(hearts[i]);
                if (heartBreak != nullptr)
                    heartBreak->draw(window);

                p->drawSprite(window, time);

                for (int i = 0; i < 2; ++i) {
                    if (runOne != nullptr)
                        runOne->draw(window);
                    if (runTwo != nullptr)
                        runTwo->draw(window);
                }
                if (runExplode != nullptr)
                    runExplode->draw(window);

                if (p->drop != nullptr)
                    p->drawDrop(window);

                for (int i = 0; i < bosses.size(); ++i)
                    bosses[i]->draw(window);
                for (int i = 0; i < (p->bullets.size()); ++i) {
                    p->bullets[i].draw(window);
                }

                for (int i = 0; i < invaders.size(); ++i) {
                    invaders[i]->draw(window);
                    invaders[i]->drawVent(window);
                    invaders[i]->drawBomb(window);
                    invaders[i]->drawExplosion(window);
                }

                if (level.sans()) {
                    dynamic_cast<Sans*>(bosses[0])->phaseFive(time, window, p, deltaTime);
                    dynamic_cast<Sans*>(bosses[0])->phaseSix(time, window, p, deltaTime);
                    dynamic_cast<Sans*>(bosses[0])->phaseSeven(time, window, p, deltaTime);
                    dynamic_cast<Sans*>(bosses[0])->phaseEight(time, window, p, deltaTime);
                }
            }
            window.display();

        }
    }

};