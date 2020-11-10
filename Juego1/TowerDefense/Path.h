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
	void show();

private:

	bool pathMatrix[15][20];

	void init();
	bool get(Point* point);
};

