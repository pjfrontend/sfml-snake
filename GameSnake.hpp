#pragma once
#include <string>
#include <cmath>
#include "IAppState.hpp"
#include "Constants.hpp"

class GameSnake : public IAppState
{
	sf::Font font;
	sf::Text txt_score;
	void add_snake_segment(float dtAsSeconds);
	bool isInBounds(sf::Vector2f pos);
	void eat_apple(float dtAsSeconds);

public:
	void start(GameData *gameData);
	void update(float dtAsSeconds);
	void draw();
};
