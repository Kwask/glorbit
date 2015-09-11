#ifndef DEBUG_H
#define DEBUG_H

const bool DEBUG = true; // set to true to enable debug messages

#include <iostream>
#include <string>

// displays a debug message if debug mode is active
void debugging( std::string message )
{
	if( DEBUG )
	{
		fprintf( stdout, "%s\n", message.c_str() );
	}
}

#endif