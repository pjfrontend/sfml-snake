// based on the rhythm game project

#include "Engine.hpp"

int main()
{

	Engine engine;
	engine.request(STATE_START);
	engine.start();

	return EXIT_SUCCESS;
}
