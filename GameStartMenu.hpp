#pragma once
#include "IAppState.hpp"
#include "Constants.hpp"

class GameStartMenu : public IAppState
{
	constexpr static float LEFT_MARGIN = 20.0f;
	bool is_clicking = false;
	sf::Font font;
	sf::Text title;
	sf::Text new_game;
	sf::Text quit;

public:
	void start(GameData *gameData);
	void update(float dtAsSeconds);
	void draw();
};
