#include "Menu.h"


Menu::Menu() {
	if (!mainFont.loadFromFile("fonts/DTM-Mono.otf")) {
		std::cout << "Error loading font...\n";
		exit(1);
	}
	titleFont.loadFromFile("fonts/logofont.otf");

	mainMenu = true;
	pauseMenu = false;
	showInst = false;
	scoreMenu = false;
	startGame = false;

	enteredName = false;

	restartGame = false;
	gameOver = false;
	name = "\0";
	escToMain = false;
	escToPause = false;

	badgeTex[0].loadFromFile("img/gold.png");
	badgeTex[1].loadFromFile("img/silver.png");
	badgeTex[2].loadFromFile("img/bronze.png");
	badges[0].setTexture(badgeTex[0]);
	badges[1].setTexture(badgeTex[1]);
	badges[2].setTexture(badgeTex[2]);

	invsTex[0].loadFromFile("img/invadersprites/alpha.png");
	invsTex[1].loadFromFile("img/invadersprites/beta.png");
	invsTex[2].loadFromFile("img/invadersprites/gamma.png");
	for (int i = 0; i < 3; ++i)
		invs[i].setTexture(invsTex[i]);

	skelHead.loadFromFile("img/sans/faces/bad-o-clock.png");
	skeleton.setTexture(skelHead);

	keyTex.loadFromFile("img/keys.png");
	keys.setTexture(keyTex);
	keys.setScale(0.25, 0.25);

	option = 1;
	max = 3;

	for (int i = 0; i < 5; ++i)
		scores[i] = 0;

	for (int i = 0; i < 2; ++i)
		moveText[i] = false;

	menuBg = nullptr;

	for (int i = 0; i < 7; ++i) {
		text[i].setFont(mainFont);
		text[i].setFillColor(sf::Color::White);
		text[i].setCharacterSize(30);
	}

	for (int i = 0; i < 5; ++i) {
		scoreText[i].setFont(mainFont);
		scoreText[i].setFillColor(sf::Color::White);
		scoreText[i].setCharacterSize(50);
	}


}

void Menu::moveUp() {
	if (option == 1) {
		text[option].setFillColor(sf::Color::White);
		text[option].setPosition(textPos[option].x, textPos[option].y);
		text[max - 1].setFillColor(sf::Color::Yellow);
		option = max - 1;
	}
	else if (option > 1) {
		text[option].setFillColor(sf::Color::White);
		text[option].setPosition(textPos[option].x, textPos[option].y);
		text[option - 1].setFillColor(sf::Color::Yellow);
		--option;
	}
}

void Menu::moveDown() {
	if (option + 1 == max) {
		text[1].setFillColor(sf::Color::Yellow);
		text[option].setFillColor(sf::Color::White);
		text[option].setPosition(textPos[option].x, textPos[option].y);

		option = 1;
	}
	else if (option + 1 < max) {
		text[option].setFillColor(sf::Color::White);
		text[option].setPosition(textPos[option].x, textPos[option].y);
		text[option + 1].setFillColor(sf::Color::Yellow);
		++option;
	}
}

void Menu::resetMove() {
	for (int i = 0; i < 2; ++i)
		moveText[i] = false;
}

void Menu::displayMain(sf::RenderWindow& window, sf::Texture& tex, float time) {


	deltaTime = clk.restart();

	max = 6;
	if (menuBg == nullptr) {
		menuBg = new Animation(0.12, 16, tex, true);
		menuBg->animate(vector2f(0, 0));
	}

	sf::Event e;
	while (window.pollEvent(e)) {

		if (e.type == sf::Event::Closed)
			window.close();

		if (e.key.code == sf::Keyboard::Enter) {
			if (option == 1) {
				mainMenu = false;
				restartGame = true;
				startGame = true;
			}
			
			if (option == 2) {
				mainMenu = false;
				showInst = true;
				escToMain = true;
				escToPause = false;
			}

			if (option == 3) {
				mainMenu = false;
				escToPause = false;
				escToMain = true;
				scoreMenu = true;
			}

			if (option == 4) {
				resetMove();
				mainMenu = false;
				optionsMenu = true;
				escToPause = false;
				escToMain = true;
				option = 1;
			}

			if (option == 5) {
				window.close();
			}
		}

		if (e.type == sf::Event::KeyReleased) {
			if (e.key.code == sf::Keyboard::Down || e.key.code == sf::Keyboard::S)
				moveDown();
			if (e.key.code == sf::Keyboard::Up || e.key.code == sf::Keyboard::W)
				moveUp();
		}
	}

	window.clear();
	menuBg->timer += time;
	menuBg->update(true);
	menuBg->draw(window);

	for (int i = 0; i < max; ++i)
		text[i].setFillColor(sf::Color::White);

	moveSelectedText();
	text[option].setFillColor(sf::Color::Yellow);

	text[0].setFont(titleFont);
	text[0].setCharacterSize(70);
	text[0].setString("HELLASUS");
	text[0].setPosition(465, 50);


	text[1].setString("Play");
	text[1].setCharacterSize(50);
	if (option != 1 || text[1].getPosition().x < 625 || text[1].getPosition().x > 654)
		text[1].setPosition(639, 200);

	textPos[1] = vector2f(639, 200);

	text[2].setString("Help");
	text[2].setCharacterSize(50);
	if (option != 2 || text[2].getPosition().x < 625 || text[2].getPosition().x > 654)
		text[2].setPosition(639, 300);
	textPos[2] = vector2f(639, 300);

	text[3].setString("Scores");
	text[3].setCharacterSize(50);
	if (option != 3 || text[3].getPosition().x < 625 || text[3].getPosition().x > 654)
		text[3].setPosition(639, 400);
	textPos[3] = vector2f(639, 400);

	text[4].setString("Options");
	text[4].setCharacterSize(50);
	if (option != 4 || text[4].getPosition().x < 625 || text[4].getPosition().x > 654)
		text[4].setPosition(639, 500);
	textPos[4] = vector2f(639, 500);

	text[5].setString("Exit");
	text[5].setCharacterSize(50);
	if (option != 5 || text[5].getPosition().x < 625 || text[5].getPosition().x > 654)
		text[5].setPosition(639, 600);
	textPos[5] = vector2f(639, 600);

	window.draw(text[0]);



	window.draw(text[1]);

	window.draw(text[2]);
	window.draw(text[3]);
	window.draw(text[4]);
	window.draw(text[5]);

}

void Menu::displayScore(sf::RenderWindow& window, sf::Texture& tex, float time)
{
	deltaTime = clk.restart();

	window.clear();
	menuBg->timer += time;
	menuBg->update(true);
	menuBg->draw(window);

	if (menuBg == nullptr) {
		menuBg = new Animation(0.12, 16, tex, true);
		menuBg->animate(vector2f(0, 0));
	}

	sf::Event e;

	while (window.pollEvent(e)) {
		if (e.type == sf::Event::Closed)
			window.close();
		else if (e.key.code == sf::Keyboard::Escape) {
			if (escToMain == true) {
				mainMenu = true;
				scoreMenu = false;
				option = 3;
			}
			else if (escToPause == true) {
				pauseMenu = true;
				scoreMenu = false;
				option = 4;
			}
		}
	}

	std::ifstream file("highscores.txt");

	if (file.is_open()) {

		int track = 0;
		while (track < 5) {
			file >> names[track] >> scores[track];
			++track;
		}

		for (int i = 0; i < 5; ++i)
			for (int j = 0; j < 4; ++j)
				if (scores[j + 1] > scores[j]) {
					int tmp = scores[j + 1];
					string tmpName = names[j + 1];

					scores[j + 1] = scores[j];
					scores[j] = tmp;
					names[j + 1] = names[j];
					names[j] = tmpName;
				}

		for (int i = 0; i < 5; ++i) {
			scoreText[i].setString(names[i] + " " + to_string(scores[i]));
			scoreText[i].setPosition(639, 150 + (i * 100));
			window.draw(scoreText[i]);
		}
		file.close();

	}
	for (int i = 0; i < 3; ++i) {
		badges[i].setScale(0.25, 0.25);
		badges[i].setPosition(550, 160 + (i * 95));
		window.draw(badges[i]);
	}

	moveSelectedText();
}

void Menu::displayOptions(sf::RenderWindow& window, sf::Sprite& bg, sf::Texture* bgTex, float time, sf::Music* themes, int& chosenMusic, int& chosenBg) {
	deltaTime = clk.restart();

	window.clear();
	bg.setTexture(bgTex[chosenBg]);
	window.draw(bg);

	max = 3;

	sf::Event e;
	while (window.pollEvent(e)) {

		if (e.type == sf::Event::Closed)
			window.close();

		if (e.key.code == sf::Keyboard::Escape) {
			if (escToMain == true) {
				resetMove();
				mainMenu = true;
				optionsMenu = false;
				option = 4;
			}
			else if (escToPause == true) {
				resetMove();
				pauseMenu = true;
				optionsMenu = false;
				option = 5;
			}
		}

		if (e.type == sf::Event::KeyReleased) {
			if (e.key.code == sf::Keyboard::Down || e.key.code == sf::Keyboard::S)
				moveDown();
			if (e.key.code == sf::Keyboard::Up || e.key.code == sf::Keyboard::W)
				moveUp();
			if (e.key.code == sf::Keyboard::Right || e.key.code == sf::Keyboard::D) {
				if (option == 1) {
					if (chosenMusic < 4)
						++chosenMusic;
					else
						chosenMusic = 0;
				}
				else if (option == 2) {
					if (chosenBg < 3)
						++chosenBg;
					else
						chosenBg = 0;
				}
			}
			if (e.key.code == sf::Keyboard::Left || e.key.code == sf::Keyboard::A) {
				if (option == 1) {
					if (chosenMusic > 0)
						--chosenMusic;
					else
						chosenMusic = 4;
				}
				else if (option == 2) {
					if (chosenBg > 0)
						--chosenBg;
					else
						chosenBg = 3;
				}
			}
		}

	}

	moveSelectedText();
	text[option].setFillColor(sf::Color::Yellow);

	text[1].setString("Change Track: ");
	text[1].setCharacterSize(50);
	if (option != 1 || text[1].getPosition().x < 285 || text[1].getPosition().x > 315)
		text[1].setPosition(300, 150);
	textPos[1] = vector2f(300, 150);

	text[2].setString("Change Background: ");
	text[2].setCharacterSize(50);
	if (option != 2 || text[2].getPosition().x < 285 || text[2].getPosition().x > 315)
		text[2].setPosition(300, 300);
	textPos[2] = vector2f(300, 300);

	text[3].setString("Song " + to_string(chosenMusic + 1));
	text[3].setCharacterSize(50);
	text[3].setPosition(850, 150);
	text[3].setFillColor(sf::Color::White);

	text[4].setString("Background " + to_string(chosenBg + 1));
	text[4].setCharacterSize(50);
	text[4].setPosition(850, 300);
	text[4].setFillColor(sf::Color::White);

	window.draw(text[1]);

	window.draw(text[2]);
	window.draw(text[3]);
	window.draw(text[4]);

}

void Menu::displayInst(sf::RenderWindow& window, sf::Texture&, float time) {
	deltaTime = clk.restart();
	max = 0;

	window.clear();
	menuBg->timer += time;
	menuBg->update(true);
	menuBg->draw(window);

	sf::Event e;
	while (window.pollEvent(e)) {

		if (e.type == sf::Event::Closed)
			window.close();

		if (e.key.code == sf::Keyboard::Escape) {
			if (escToMain == true) {
				showInst = false;
				mainMenu = true;
				option = 2;
			}
			else if (escToPause == true) {
				showInst = false;
				pauseMenu = true;
				option = 3;
			}
		}
	}

	keys.setPosition(65, 75);
	window.draw(keys);

	text[1].setString("WASD or Arrow keys to move.");
	text[1].setFillColor(sf::Color::White);
	text[1].setPosition(100, 250);
	window.draw(text[1]);

	text[2].setString("SPACE to fire.");
	text[2].setFillColor(sf::Color::White);
	text[2].setPosition(100, 350);
	window.draw(text[2]);

	text[3].setString("Defeat enemies for points.");
	text[3].setFillColor(sf::Color::White);
	text[3].setPosition(100, 450);
	window.draw(text[3]);

	invs[0].setPosition(95, 550);
	window.draw(invs[0]);

	text[4].setString(" - 10");
	text[4].setFillColor(sf::Color::White);
	text[4].setPosition(150, 560);
	window.draw(text[4]);

	invs[1].setPosition(400, 550);
	window.draw(invs[1]);

	text[4].setString(" - 15");
	text[4].setFillColor(sf::Color::White);
	text[4].setPosition(455, 560);
	window.draw(text[4]);

	invs[2].setPosition(705, 560);
	window.draw(invs[2]);

	text[4].setString(" - 20");
	text[4].setFillColor(sf::Color::White);
	text[4].setPosition(760, 560);
	window.draw(text[4]);

	skeleton.setPosition(1010, 560);
	window.draw(skeleton);

	text[4].setString(" - ???");
	text[4].setFillColor(sf::Color::White);
	text[4].setPosition(1065, 560);
	window.draw(text[4]);


}

void Menu::displayPause(sf::RenderWindow& window, sf::Texture& tex, float time, float& pauseTime) {
	deltaTime = clk.restart();
	pauseTime += deltaTime.asSeconds();

	max = 7;
	if (menuBg == nullptr) {
		menuBg = new Animation(0.12, 16, tex, true);
		menuBg->animate(vector2f(0, 0));
	}

	sf::Event e;
	while (window.pollEvent(e)) {

		if (e.type == sf::Event::Closed)
			window.close();

		if (e.key.code == sf::Keyboard::Enter) {
			if (option == 1) {
				pauseMenu = false;
				startGame = true;
			}

			if (option == 2) {
				restartGame = true;
				startGame = true;
				pauseMenu = false;
			}

			if (option == 3) {
				pauseMenu = false;
				showInst = true;
				escToMain = false;
				escToPause = true;
			}

			if (option == 4) {
				pauseMenu = false;
				escToPause = true;
				escToMain = false;
				scoreMenu = true;
			}

			if (option == 5) {
				resetMove();
				pauseMenu = false;
				optionsMenu = true;
				escToPause = true;
				escToMain = false;
				option = 1;
			}

			if (option == 6) {
				window.close();
			}
		}

		if (e.type == sf::Event::KeyReleased) {
			if (e.key.code == sf::Keyboard::Down || e.key.code == sf::Keyboard::S)
				moveDown();
			if (e.key.code == sf::Keyboard::Up || e.key.code == sf::Keyboard::W)
				moveUp();
		}
	}

	window.clear();
	menuBg->timer += time;
	menuBg->update(true);
	menuBg->draw(window);

	for (int i = 0; i < max; ++i)
		text[i].setFillColor(sf::Color::White);

	moveSelectedText();
	text[option].setFillColor(sf::Color::Yellow);

	text[0].setFont(titleFont);
	text[0].setCharacterSize(70);
	text[0].setString("HELLASUS");
	text[0].setPosition(465, 50);


	text[1].setString("Resume");
	text[1].setCharacterSize(50);
	if (option != 1 || text[1].getPosition().x < 625 || text[1].getPosition().x > 654)
		text[1].setPosition(639, 150);

	textPos[1] = vector2f(639, 150);

	text[2].setString("Restart");
	text[2].setCharacterSize(50);
	if (option != 2 || text[2].getPosition().x < 625 || text[2].getPosition().x > 654)
		text[2].setPosition(639, 250);

	textPos[2] = vector2f(639, 250);

	text[3].setString("Help");
	text[3].setCharacterSize(50);
	if (option != 3 || text[3].getPosition().x < 625 || text[3].getPosition().x > 654)
		text[3].setPosition(639, 350);
	textPos[3] = vector2f(639, 350);

	text[4].setString("Scores");
	text[4].setCharacterSize(50);
	if (option != 4 || text[4].getPosition().x < 625 || text[4].getPosition().x > 654)
		text[4].setPosition(639, 450);
	textPos[4] = vector2f(639, 450);

	text[5].setString("Options");
	text[5].setCharacterSize(50);
	if (option != 5 || text[5].getPosition().x < 625 || text[5].getPosition().x > 654)
		text[5].setPosition(639, 550);
	textPos[5] = vector2f(639, 550);

	text[6].setString("Exit");
	text[6].setCharacterSize(50);
	if (option != 6 || text[6].getPosition().x < 625 || text[6].getPosition().x > 654)
		text[6].setPosition(639, 650);
	textPos[6] = vector2f(639, 650);

	for (int i = 0; i < 7; ++i)
		window.draw(text[i]);

	window.display();
}

void Menu::showGameOver(sf::RenderWindow& window, sf::Texture& tex, float time, int score, char temp)
{
	window.clear();
	menuBg->timer += time;
	menuBg->update(true);
	menuBg->draw(window);

	text[1].setString("Enter your name: ");
	text[1].setPosition(100, 350);
	text[1].setFillColor(sf::Color::White);

	text[2].setString("");
	text[2].setPosition(600, 350);
	text[2].setFillColor(sf::Color::White);

	sf::Event e;


	while (window.pollEvent(e)) {
		if (e.type == sf::Event::Closed)
			window.close();

		if (e.type == sf::Event::TextEntered) {
			if ((e.text.unicode >= 65 && e.text.unicode <= 91) || (e.text.unicode >= 97 && e.text.unicode <= 122)) {
				temp = e.text.unicode;
				name += temp;
			}
			if (e.text.unicode == 8 && name != "\0")
				name.pop_back();
		}
		if (e.type == sf::Event::KeyReleased)
			if (e.key.code == sf::Keyboard::Enter)
				enteredName = true;
	}

	text[2].setString(name);

	window.draw(text[1]);
	window.draw(text[2]);

	if (enteredName) {
		string names[6]{};
		int scores[6]{};

		fstream file("highscores.txt", ios::in | ios::out);

		int track = 0;
		int storeScore;
		string storeName;

		while (file >> storeName >> storeScore && track < 5) {
			names[track] = storeName;
			scores[track] = storeScore;
			track++;
		}

		if (track < 5 || score > scores[track - 1]) {
			scores[track] = score;
			names[track] = name;

			for (int i = 0; i < track; ++i) {
				for (int j = track; j > 0; --j) {
					if (scores[j] > scores[j - 1]) {
						int tmp = scores[j];
						string tmpName = names[j];

						scores[j] = scores[j - 1];
						names[j] = names[j - 1];
						scores[j - 1] = tmp;
						names[j - 1] = tmpName;
					}
				}
			}

			file.close();
			file.open("highscores.txt", ios::out | ios::trunc);

			for (int i = 0; i < track + 1; i++) {
				file << names[i] << " " << scores[i] << endl;
			}
		}

		gameOver = false;
		mainMenu = true;
		option = 1;
		file.close();
	}

	window.display();
}

void Menu::pauseGame()
{
	pauseMenu = true;
	startGame = false;
}

void Menu::moveSelectedText() {
	if (moveText[0] == false) {
		if (text[option].getPosition().x >= textPos[option].x - 5)
			text[option].move(-0.01 * deltaTime.asSeconds() * 1000, 0);
		else
			moveText[0] = true;
	}
	if (moveText[0] == true) {
		if (text[option].getPosition().x <= textPos[option].x + 5)
			text[option].move(0.01 * deltaTime.asSeconds() * 1000, 0);
		else
			moveText[0] = false;
	}
	if (moveText[1] == false) {
		if (text[option].getPosition().y >= textPos[option].y - 5)
			text[option].move(0, -0.01 * deltaTime.asSeconds() * 1000);
		else
			moveText[1] = true;
	}
	if (moveText[1] == true) {
		if (text[option].getPosition().y <= textPos[option].y + 5)
			text[option].move(0, 0.01 * deltaTime.asSeconds() * 1000);
		else
			moveText[1] = false;
	}
}