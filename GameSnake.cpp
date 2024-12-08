#include "GameSnake.hpp"

void GameSnake::start(GameData *gameData)
{
	this->gameData = gameData;

	font.loadFromFile(FONT_NAME);

	txt_score.setFont(font);
	txt_score.setPosition(20.0f, 20.0f);
	txt_score.setColor(WHITE);
	txt_score.setCharacterSize(30);
}

void GameSnake::update(float dtAsSeconds)
{
	// input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		gameData->publisher->notify((void *)STATE_PAUSE.c_str());
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		gameData->snake_head_direction_facing = left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		gameData->snake_head_direction_facing = right;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		gameData->snake_head_direction_facing = up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		gameData->snake_head_direction_facing = down;
	}

	// update head
	auto head = &gameData->snake_segment_sprites.at(0);
	auto direction = gameData->snake_head_direction_facing;
	auto m_Speed = gameData->snake_speed;
	if (direction == right)
	{
		head->move(m_Speed * dtAsSeconds, 0);
	}
	else if (direction == left)
	{
		head->move(-m_Speed * dtAsSeconds, 0);
	}
	else if (direction == down)
	{
		head->move(0, m_Speed * dtAsSeconds);
	}
	else
	{
		head->move(0, -m_Speed * dtAsSeconds);
	}

	if (head->getGlobalBounds().intersects(gameData->apple.getGlobalBounds()))
	{
		eat_apple(dtAsSeconds);
	}
	txt_score.setString(TXT_SCORE + std::to_string(gameData->snake_segment_sprites.size() - 1));

	if (!isInBounds(head->getPosition()))
	{
		gameData->publisher->notify((void *)STATE_START.c_str());
	}

	// update segments
	for (size_t i = 1; i < gameData->snake_segment_sprites.size(); i += 1)
	{
		// printf("i = %d\n", i);
		auto current_segment = &gameData->snake_segment_sprites.at(i);
		auto current_pos = current_segment->getPosition();
		auto prev_pos = gameData->snake_segment_sprites.at(i - 1).getPosition();
		current_segment->move((prev_pos - current_pos) * dtAsSeconds * 2.0f);
	}
}

void GameSnake::draw()
{
	gameData->sceneTexture.clear();
	for (size_t i = 1; i < gameData->snake_segment_sprites.size(); i++)
	{
		gameData->sceneTexture.draw(gameData->snake_segment_sprites.at(i));
	}
	gameData->sceneTexture.draw(gameData->apple);
	gameData->sceneTexture.draw(gameData->snake_segment_sprites.at(0));
	gameData->sceneTexture.display();

	gameData->brightTexture.clear();
	sf::Sprite sceneSprite(gameData->sceneTexture.getTexture());
	gameData->brightTexture.draw(sceneSprite, &gameData->thresholdShader);
	gameData->brightTexture.display();

	gameData->blurTexture.clear();
	sf::Sprite brightSprite(gameData->brightTexture.getTexture());
	gameData->blurTexture.draw(brightSprite, &gameData->blurShader);
	gameData->blurTexture.display();

	gameData->window->clear(BG);
	sf::Sprite blurSprite(gameData->blurTexture.getTexture());
	gameData->combineShader.setUniform("original", gameData->sceneTexture.getTexture());
	gameData->combineShader.setUniform("bloom", gameData->blurTexture.getTexture());
	gameData->window->draw(blurSprite, &gameData->combineShader);

	gameData->window->draw(txt_score);
	gameData->window->display();
}

void GameSnake::add_snake_segment(float dtAsSeconds)
{
	auto last_pos = gameData->snake_segment_sprites.back().getPosition();
	Facing direction = gameData->snake_head_direction_facing;

	auto segment = sf::CircleShape(HALF_TILE);
	segment.setFillColor(WHITE);
	if (direction == left)
	{
		segment.setPosition(last_pos.x + TILE_SIZE, last_pos.y);
	}
	else if (direction == right)
	{
		segment.setPosition(last_pos.x - TILE_SIZE, last_pos.y);
	}
	else if (direction == up)
	{
		segment.setPosition(last_pos.x, last_pos.y + TILE_SIZE);
	}
	else
	{
		segment.setPosition(last_pos.x, last_pos.y - TILE_SIZE);
	}

	gameData->snake_segment_sprites.push_back(segment);
}

bool GameSnake::isInBounds(sf::Vector2f pos)
{
	return pos.x >= 0.0f && pos.y >= 0.0f && pos.x < (float)(WIDTH_IN_PIXELS - TILE_SIZE) && pos.y < (float)(HEIGHT_IN_PIXELS - TILE_SIZE);
}

void GameSnake::eat_apple(float dtAsSeconds)
{
	auto random_number = 123456789 * dtAsSeconds;
	auto prev_pos = gameData->apple.getPosition();
	auto new_x = static_cast<int>(prev_pos.x + random_number) % (WIDTH_IN_PIXELS - TILE_SIZE);
	auto new_y = static_cast<int>(prev_pos.y + random_number) % (HEIGHT_IN_PIXELS - TILE_SIZE);
	gameData->apple.setPosition(new_x, new_y);
	add_snake_segment(dtAsSeconds);
	gameData->snake_speed += 10;
}
