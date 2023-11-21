#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "vector2f.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

enum themes {
    core,
    asgore,
    glamour,
    jevil,
    queen,
    THEME_NUM
};

using namespace std;

class Menu
{
    sf::Font mainFont;
    sf::Font titleFont;
    sf::Text text[7];
    sf::Sprite menuBox;
    sf::Sprite badges[3];
    sf::Texture badgeTex[3];
    sf::Texture boxTexture;
    sf::Clock clk;
    sf::Time deltaTime;
    vector2f textPos[7];
    bool moveText[2];
    string name;

    sf::Sprite keys;
    sf::Texture keyTex;

    sf::Sprite invs[3];
    sf::Texture invsTex[3];

    sf::Sprite skeleton;
    sf::Texture skelHead;

    string names[5];
    int scores[5];
    sf::Text scoreText[5];

    Animation* menuBg;
    int option, max;
    bool mainMenu, pauseMenu, showInst, optionsMenu, scoreMenu, startGame, restartGame;
    bool gameOver;
    bool enteredName;
    bool escToMain, escToPause;

public:
    Menu();
    
    void displayMain(sf::RenderWindow& window, sf::Texture&, float time);
    void displayInst(sf::RenderWindow& window, sf::Texture&, float time);
    void displayScore(sf::RenderWindow& window, sf::Texture&, float time);
    void displayOptions(sf::RenderWindow& window, sf::Sprite&, sf::Texture*, float time, sf::Music*, int&, int&);
    void displayPause(sf::RenderWindow& window, sf::Texture&, float time, float& pauseTime);

    void showGameOver(sf::RenderWindow& window, sf::Texture&, float time, int score, char);

    void pauseGame();

    void resetMove();
    bool restart() const { return restartGame; }
    bool showMain() const { return mainMenu; }
    bool showHelp() const { return showInst; }
    bool showPause() const { return pauseMenu; }
    bool showScore() const { return scoreMenu; }
    bool playGame() const { return startGame; }
    bool showOptions() const { return optionsMenu; }
    bool isGameOver() const { return gameOver; }

    void moveSelectedText();

    void setRestart(bool n) { restartGame = n; }
    void setGameOver(bool n) { gameOver = n; }
    void setStartGame(bool n) { startGame = n; }

    void moveUp();
    void moveDown();

};


