#ifndef ENGINE_H
#define ENGINE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "glfwFuncs.h"
#include "mesh.h"
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
	bool GLFWInitialized_ = false;

	unsigned long long iteration_ = 0;

	GLFWwindow* screen_;

	EngineState status_ = EngineState::OFF;	

	Mesh triangle_;

public:
	Engine();
	~Engine();
	
	unsigned long long iteration(); // Returns the iteration of the engine
	
	EngineState status(); // Returns the status of the engine
	
	void initialize(); // Initializes variables
	void initializeGLFW(); // Initializes GLFW, is called inside initialize()
	void start(); // Is used to start the engine, will initialize varaibles if they are not already initialized
	void stop(); // Is used to stop the engine, will destruct variables if they are not already destructed
	void stopGLFW(); // Stops GLFW
	void process(); // Processes a single tick of the game
	void pollEvents(); // Polls any events that might have happened
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

	GLFWInitialized_ = false;
	iteration_ = 0;

	initializeGLFW();

	status( EngineState::INITIALIZED );
	debugging( "ENGINE INITIALIZED." );
}

void Engine::initializeGLFW()
{
	debugging( "GLFW initiliazing..." );
	//initialization code goes here
	screen_ = nullptr;
	glfwSetErrorCallback( errorCallback );

	if( !glfwInit() )
	{
		exit( EXIT_FAILURE );
	}

	debugging( "GLFW creating window..." );
	screen_ = glfwCreateWindow( 640, 480, "Glorbit", 0, 0 );
	if( !screen_ )
	{
		debugging( "ERROR: GLFW FAO;ED TP CREATE WINDOW" );
		glfwTerminate();
		exit( EXIT_FAILURE );
	}

	glfwMakeContextCurrent( screen_ );
	debugging( "GLFW successfully created the window." );
	glfwSwapInterval(1);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if( err != GLEW_OK )
	{
		debugging( "ERROR: GLEW FAILED TO INITILIALIZE" );
		glfwTerminate();
		exit( EXIT_FAILURE );
	}
/*
	std::string glew_version( "Using GLEW Version: " );
	glew_version += glewGetString( GLEW_VERSION );
	debugging( glew_version );
*/

	debugging( "Generating triangle VBO..." );
	triangle_.generate_vertex_buffer();
	debugging( "Generated triangle VBO." );

	glfwSetKeyCallback( screen_, keyCallback );

	GLFWInitialized_ = true;
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
	if( GLFWInitialized_ )
	{
		stopGLFW();
	}

	status( EngineState::OFF );
	debugging( "ENGINE STOPPED." );
}

void Engine::stopGLFW()
{
	debugging( "GLFW stopping..." );
	glfwDestroyWindow( screen_ );
	glfwTerminate();

	GLFWInitialized_ = false;
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

	render();
	pollEvents();
}

void Engine::pollEvents()
{
	glfwPollEvents();

	if( glfwWindowShouldClose( screen_ ))
	{
		status( EngineState::SHOULD_QUIT );
	}
}

// Draws the game to the screen
void Engine::render()
{
	triangle_.render();

	glfwSwapBuffers( screen_ );
}

// Sets the status of the game engine
void Engine::status( EngineState state )
{
	status_ = state;
}

#endif