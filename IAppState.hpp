#pragma once
#include "GameData.hpp"

class IAppState
{
public:
	virtual void start(GameData *gameData) = 0;
	virtual void update(float dtAsSeconds) = 0;
	virtual void draw() = 0;

protected:
	GameData *gameData;
};