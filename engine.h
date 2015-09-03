#ifndef ENGINE_H
#define ENGINE_H

#include <GLFW/glfw3.h>
#include "glfwFuncs.h"
#include "debug.h"

enum class EngineState
{
	OFF,
	STARTED,
	INITIALIZED,
	NORMAL,
	SHOULD_QUIT,
	DESTRUCTING
};

class Engine
{
private:
	GLFWwindow* screen;

	EngineState status_ = EngineState::OFF;	

	bool GLFWInitialized = false;

	unsigned long long iteration_ = 0;

public:
	Engine();
	~Engine();

	unsigned long long iteration(); // Returns the iteration of the engine

	EngineState status(); // Returns the status of the engine

	void initialize(); // Initializes variables
	void initializeGLFW(); // Initializes GLFW, is called inside initialize();
	void start(); // Is used to start the engine, will initialize varaibles if they are not already initialized
	void stop(); // Is used to stop the engine, will destruct variables if they are not already destructed
	void stopGLFW(); // Stops GLFW
	void process(); // Processes a single tick of the game
	void render(); // Draws objects to the screen
	void status( EngineState state ); // Sets the status of the engine

};

Engine::Engine()
{
	if( status() == EngineState::OFF )
	{
		initialize();
	}
}

Engine::~Engine()
{
	if( status() != EngineState::OFF )
	{
		stop();
	}
}

unsigned long long Engine::iteration()
{
	return iteration_;
}

EngineState Engine::status()
{
	return status_;
}

void Engine::initialize()
{
	debugging( "ENGINE INITIALIZING..." );
	status( EngineState::STARTED );

	GLFWInitialized = false;
	iteration_ = 0;

	initializeGLFW();

	status( EngineState::INITIALIZED );
	debugging( "ENGINE INITIALIZED." );
}

void Engine::initializeGLFW()
{
	debugging( "GLFW initiliazing..." );
	//initialization code goes here
	screen = nullptr;
	glfwSetErrorCallback( errorCallback );

	if( !glfwInit() )
	{
		exit( EXIT_FAILURE );
	}

	screen = glfwCreateWindow( 640, 480, "Glorbit", NULL, NULL );
	if( !screen )
	{
		glfwTerminate();
		exit( EXIT_FAILURE );
	}

	glfwMakeContextCurrent( screen );
	glfwSwapInterval(1);

	glfwSetKeyCallback( screen, keyCallback );

	GLFWInitialized = true;
	debugging( "GLFW successfully initialized." );
}

void Engine::start()
{
	debugging( "ENGINE STARTING..." );
	if( status() == EngineState::OFF )
	{
		initialize();
	}


	status( EngineState::NORMAL );
	debugging( "ENGINE STARTED." );
}

// destructs the contents of the engine and shuts it down
void Engine::stop()
{
	debugging( "ENGINE STOPPING..." );
	status( EngineState::DESTRUCTING );

	// destruction code goes here
	if( GLFWInitialized )
	{
		stopGLFW();
	}

	status( EngineState::OFF );
	debugging( "ENGINE STOPPED." );
}

void Engine::stopGLFW()
{
	debugging( "GLFW stopping..." );
	glfwDestroyWindow( screen );
	glfwTerminate();

	GLFWInitialized = false;
	debugging( "GLFW stopped." );
}

// Processes a single tick of the game
void Engine::process()
{
	// If the engine isn't running normally, don't process
	if( status() != EngineState::NORMAL )
	{
		return;
	}

	if( glfwWindowShouldClose( screen ))
	{
		status( EngineState::SHOULD_QUIT );
	}

	render();
	glfwPollEvents();
}

// Draws the game to the screen
void Engine::render()
{
	glfwSwapBuffers( screen );
}

// Sets the status of the game engine
void Engine::status( EngineState state )
{
	status_ = state;
}

#endif