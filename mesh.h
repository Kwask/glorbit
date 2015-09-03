#ifndef MESH_H
#define MESH_H

#include "point.h"

class Mesh
{
private:
	Point origin;
public:
	Mesh();
	~Mesh();

	void render();

};

#endif