#include "Engine.hpp"

void AppStateSubscriber::start(Engine *engine)
{
	this->engine = engine;
}

void AppStateSubscriber::update(Publisher *who, void *what)
{
	const char *message = static_cast<char *>(what);
	// std::cout << message << std::endl;
	this->engine->request(message);
}

Engine::Engine() : FSM("GameFSM")
{
	// FSM /////////////////////
	ADD_STATE(Engine, StartState);
	ADD_STATE(Engine, PauseState);
	ADD_STATE(Engine, SnakeState);

	ADD_TRANSITION(StartState, SnakeState);
	ADD_TRANSITION(PauseState, SnakeState);
	ADD_TRANSITION(PauseState, StartState);
	ADD_TRANSITION(SnakeState, PauseState);
	ADD_TRANSITION(SnakeState, StartState);
	// FSM /////////////////////

	publisher = new Publisher();
	appStateSubscriber = new AppStateSubscriber();
	appStateSubscriber->start(static_cast<Engine *>(this));
	publisher->subscribe(appStateSubscriber);

	settings.antialiasingLevel = 8;

	window.create(sf::VideoMode(WIDTH_IN_PIXELS, HEIGHT_IN_PIXELS),
				  TXT_GAME_TITLE,
				  sf::Style::Default,
				  settings);
	window.setFramerateLimit(60);

	if (!sf::Shader::isAvailable())
	{
		printf("shaders are not available...\n");
	}
	view = window.getDefaultView();
	gameData = new GameData(&window, publisher);
}

Engine::~Engine()
{
	delete publisher;
	delete appStateSubscriber;
	delete gameData;
	delete currentAppState;
}

void Engine::start()
{
	sf::Clock clock;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::Resized)
			{
				view.setSize({static_cast<float>(event.size.width),
							  static_cast<float>(event.size.height)});
				window.setView(view);
			}
		}

		sf::Time dt = clock.restart();
		float dtAsSeconds = dt.asSeconds();
		currentAppState->update(dtAsSeconds);
		currentAppState->draw();
	}
}

DEF_ENTER(Engine, PauseState)
{
	currentAppState = new GamePause;
	currentAppState->start(gameData);
}

DEF_EXIT(Engine, PauseState)
{
}

DEF_ENTER(Engine, StartState)
{
	currentAppState = new GameStartMenu;
	currentAppState->start(gameData);
	init_positions();
}

DEF_EXIT(Engine, StartState)
{
}

DEF_ENTER(Engine, SnakeState)
{
	currentAppState = new GameSnake;
	currentAppState->start(gameData);
	// example of how to call functions not from the interface
	// static_cast<GameSnake *>(currentAppState)->init_positions();
}

DEF_EXIT(Engine, SnakeState)
{
}

void Engine::init_positions()
{
	auto win_size = this->gameData->window->getSize();

	gameData->snake_segment_sprites.clear();

	gameData->apple.setRadius(HALF_TILE);
	gameData->apple.setFillColor(APPLE);
	gameData->apple.setPosition(TILE_SIZE, win_size.y / 2);

	auto head = sf::CircleShape(HALF_TILE);
	head.setFillColor(HEAD);
	head.setPosition(win_size.x / 2, win_size.y / 2);

	gameData->snake_segment_sprites.push_back(head);
	gameData->snake_head_direction_facing = left;
	gameData->snake_speed = 200;
}
