#ifndef POINT_H
#define POINT_H

struct Point
{
	Point();
	Point( const int x, const int y, const int rotation );
	~Point();

	// Position in the world
	int x;
	int y;

	// How much spin there is
	int rotation;
};

Point::Point()
{
	int x = 0;
	int y = 0;
	int rotation = 0;
}

Point::Point( const int x, const int y, const int rotation )
{
	this->x = x;
	this->y = y;
	this->rotation = rotation;
}

Point::~Point()
{

}

#endif