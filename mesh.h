#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "point.h"
#include "debug.h"

class Mesh
{
private:
	Point origin_;

	GLuint vertex_buffer_;
	GLuint vertex_ID_; // The identify ID for the VBO
	GLfloat vertex_buffer_data_[]; // The array of data for the VBO

public:
	Mesh();
	~Mesh();

	Point origin();

	GLuint vertex_ID();

	void origin( Point origin );
	void origin( int x, int y, int rotation = 0 );
	void vertex_ID( GLuint vertex_ID_ );
	void generate_vertex_buffer();
	void render();
};

Mesh::Mesh()
{

}

Mesh::~Mesh()
{

}

Point Mesh::origin()
{
	return origin_;
}

GLuint Mesh::vertex_ID()
{
	return vertex_ID_;
}

void Mesh::origin( Point origin_ )
{
	this->origin_ = origin_;
}

void Mesh::origin( int x, int y, int rotation )
{
	origin_.x = x;
	origin_.y = y;
	origin_.rotation = rotation; 
}

void Mesh::vertex_ID( GLuint vertex_ID_ )
{
	this->vertex_ID_ = vertex_ID_;
}

void Mesh::generate_vertex_buffer()
{
	debugging( "Generating vertex arrays..." );
	glGenVertexArrays( 1, &vertex_ID_ );
	debugging( "Generated vertex arrays." );

	glBindVertexArray( vertex_ID_ );
		
		GLfloat vertex_buffer_data_[] = { -1.0f, -1.0f, 0.0f,
								 1.0f, -1.0f, 0.0f,
								 0.0f,  1.0f, 0.0f, };

		debugging( "Generating vertex buffer ID..." );
		glGenBuffers( 1, &vertex_buffer_ ); // Generates one buffer and puts the resulting identifier in vertex_buffer_
		debugging( "Generating vertex buffer ID..." );

		debugging( "Binding vertex buffer ID..." );
		glBindBuffer( GL_ARRAY_BUFFER, vertex_buffer_ ); // All commands following this will be referring to vertex_buffer_
			glBufferData( GL_ARRAY_BUFFER, sizeof( vertex_buffer_data_ ), vertex_buffer_data_, GL_STATIC_DRAW ); // Linking the buffer data to the identifier
		glBindBuffer( GL_ARRAY_BUFFER, 0 ); // Unbinding the buffer
		debugging( "Bound vertex buffer ID." );

	glBindVertexArray( 0 );
}

void Mesh::render()
{
	glEnableVertexAttribArray( 0 );
		glBindBuffer( GL_ARRAY_BUFFER, vertex_buffer_ );
		glVertexAttribPointer( 0,
							   3,
							   GL_FLOAT,
							   GL_FALSE,
							   0,
							   (void*)0 );
		glDrawArrays( GL_TRIANGLES, 0, 3 );
	glDisableVertexAttribArray( 0 );
}

#endif