#include "GameData.hpp"

GameData::GameData(sf::RenderWindow *this_window, Publisher *this_publisher)
{
    window = this_window;
    publisher = this_publisher;

    if (!thresholdShader.loadFromMemory(threshold, sf::Shader::Fragment))
    {
        printf("threshold.frag didn't load\n");
    }

    if (!blurShader.loadFromMemory(blur, sf::Shader::Fragment))
    {
        printf("blur.frag didn't load\n");
    }

    if (!combineShader.loadFromMemory(combine, sf::Shader::Fragment))
    {
        printf("combine.frag didn't load\n");
    }

    if (!sceneTexture.create(WIDTH_IN_PIXELS, HEIGHT_IN_PIXELS))
    {
        printf("could not create sceneTexture\n");
    }
    if (!brightTexture.create(WIDTH_IN_PIXELS, HEIGHT_IN_PIXELS))
    {
        printf("could not create brightTexture\n");
    }
    if (!blurTexture.create(WIDTH_IN_PIXELS, HEIGHT_IN_PIXELS))
    {
        printf("could not create blurTexture\n");
    }
}

GameData::~GameData()
{
    delete window;
    delete publisher;
}