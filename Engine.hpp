#pragma once
#include "utils\fsm.hpp"
#include "utils\pubsub.hpp"
#include "IAppState.hpp"
#include "Constants.hpp"
#include "GameStartMenu.hpp"
#include "GamePause.hpp"
#include "GameData.hpp"
#include "GameSnake.hpp"

class Engine;

class AppStateSubscriber : public Subscriber
{
	Engine *engine;

public:
	void start(Engine *engine);
	virtual void update(Publisher *who, void *what);
};

class Engine : public FSM
{
	DECL_STATE(Engine, StartState);
	DECL_STATE(Engine, PauseState);
	DECL_STATE(Engine, SnakeState);

	IAppState *currentAppState;
	std::string previousStateName = "";
	sf::RenderWindow window;
	sf::Event event;
	GameData *gameData;
	Publisher *publisher;
	AppStateSubscriber *appStateSubscriber;
	sf::View view;
	void init_positions();
	sf::ContextSettings settings;

public:
	Engine();
	~Engine();
	void start();
};