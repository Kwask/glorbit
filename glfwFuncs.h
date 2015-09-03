#ifndef GLFWFUNCS_H
#define GLFWFUNCS_H

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

static void errorCallback( int error, const char* description )
{
	fputs( description, stderr );
}

static void keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
	if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
	{
		glfwSetWindowShouldClose( window, GL_TRUE );
	}
}

#endif