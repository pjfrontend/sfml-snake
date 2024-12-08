#pragma once
#include "IAppState.hpp"
#include "Constants.hpp"

class GamePause : public IAppState
{
	bool can_unpause;
	sf::Font font;
	sf::Text pause_title;
	sf::Text continue_button;
	sf::Text quit_button;

public:
	void start(GameData *gameData);
	void update(float dtAsSeconds);
	void draw();
};
