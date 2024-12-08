#include "GamePause.hpp"

void GamePause::start(GameData *gameData)
{
	this->gameData = gameData;
	can_unpause = false;
	auto win_size = this->gameData->window->getSize();

	font.loadFromFile(FONT_NAME);
	pause_title.setFont(font);
	pause_title.setString(TXT_PAUSE);
	pause_title.setCharacterSize(70);
	pause_title.setColor(WHITE);
	auto text_size = pause_title.getGlobalBounds();
	pause_title.setPosition(
		win_size.x / 2 - text_size.width / 2,
		win_size.y / 3 - text_size.height / 2);

	continue_button.setFont(font);
	continue_button.setString(TXT_CONTINUE);
	continue_button.setCharacterSize(30);
	continue_button.setColor(WHITE);
	text_size = continue_button.getGlobalBounds();
	continue_button.setPosition(
		win_size.x / 2 - text_size.width / 2,
		win_size.y / 3 - text_size.height / 2 + 120.0f);

	quit_button.setFont(font);
	quit_button.setString(TXT_QUIT);
	quit_button.setCharacterSize(30);
	quit_button.setColor(WHITE);
	text_size = quit_button.getGlobalBounds();
	quit_button.setPosition(
		win_size.x / 2 - text_size.width / 2,
		win_size.y / 3 - text_size.height / 2 + 170.0f);
}

void GamePause::update(float dtAsSeconds)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && can_unpause)
	{
		sf::Vector2f mouse = gameData->window->mapPixelToCoords(sf::Mouse::getPosition(*gameData->window));
		can_unpause = false;

		if (continue_button.getGlobalBounds().contains(mouse))
		{
			gameData->publisher->notify((void *)STATE_SNAKE.c_str());
			return;
		}

		if (quit_button.getGlobalBounds().contains(mouse))
		{
			gameData->publisher->notify((void *)STATE_START.c_str());
			return;
		}
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		can_unpause = true;
	}
}

void GamePause::draw()
{
	gameData->window->clear(BG);
	gameData->window->draw(pause_title);
	gameData->window->draw(continue_button);
	gameData->window->draw(quit_button);
	gameData->window->display();
}
