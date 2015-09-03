#include "engine.h"

int main()
{
	Engine engine;

	engine.start();

	while( engine.status() == EngineState::NORMAL )
	{
		engine.process();
	}

	engine.stop();
}