#pragma once

#include <iostream>

#include "Point.h"

using namespace std;


class Path
{
public:
	Path();

	void addPoint(int i, int j);
	Point* getNextPoint(Point* actual, Point* last);
	void show();

	int pathMatrix[15][20];

	void init();
	int get(Point* point);
};

