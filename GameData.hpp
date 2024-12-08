#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "utils/pubsub.hpp"
#include "Constants.hpp"

class GameData
{
public:
    sf::RenderWindow *window;
    Publisher *publisher;
    GameData(sf::RenderWindow *this_window, Publisher *this_publisher);
    ~GameData();

    // game specific data
    std::vector<sf::CircleShape> snake_segment_sprites;
    sf::CircleShape apple;
    Facing snake_head_direction_facing;
    int snake_speed;

    sf::Shader thresholdShader;
    sf::Shader blurShader;
    sf::Shader combineShader;

    sf::RenderTexture sceneTexture;
    sf::RenderTexture brightTexture;
    sf::RenderTexture blurTexture;
};