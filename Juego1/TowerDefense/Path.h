#pragma once

#include <iostream>

#include "Point.h"

using namespace std;


class Path
{
public:
	Path();

	void addPoint(Point* point);
	Point* getNextPoint(Point* actual, Point* last);
	Point* getStartingPoint();
	void show();

	Point* start; // Comienzo del camino

private:

	bool pathMatrix[15][20];

	void init();
	bool get(Point* point);
	int length; // Longitud del camino
	
};

