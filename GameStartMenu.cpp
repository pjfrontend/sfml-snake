#include "GameStartMenu.hpp"

void GameStartMenu::start(GameData *gameData)
{
	this->gameData = gameData;

	font.loadFromFile(FONT_NAME);

	title.setFont(font);
	title.setPosition(LEFT_MARGIN, 20.0f);
	title.setString(TXT_GAME_TITLE);
	title.setColor(WHITE);
	title.setCharacterSize(70);

	new_game.setFont(font);
	new_game.setPosition(LEFT_MARGIN, 100.0f);
	new_game.setString(TXT_NEW_GAME);
	new_game.setColor(WHITE);
	new_game.setCharacterSize(30);

	quit.setFont(font);
	quit.setPosition(LEFT_MARGIN, 140.0f);
	quit.setString(TXT_QUIT);
	quit.setColor(WHITE);
	quit.setCharacterSize(30);
}

void GameStartMenu::update(float dtAsSeconds)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !is_clicking)
	{
		is_clicking = true;
		sf::Vector2f mouse = gameData->window->mapPixelToCoords(sf::Mouse::getPosition(*gameData->window));

		if (quit.getGlobalBounds().contains(mouse))
		{
			gameData->window->close();
		}

		if (new_game.getGlobalBounds().contains(mouse))
		{
			gameData->publisher->notify((void *)STATE_SNAKE.c_str());
		}
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		is_clicking = false;
	}
}

void GameStartMenu::draw()
{
	gameData->window->clear(BG);
	gameData->window->draw(title);
	gameData->window->draw(new_game);
	gameData->window->draw(quit);
	gameData->window->display();
}