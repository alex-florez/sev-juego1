#pragma once

#include <iostream>

using namespace std;

/// <summary>
/// Representa un punto en la matriz del mapa.
/// </summary>
class Point
{
public:

	Point(int x, int y);

	int getX();
	int getY();

	bool equals(Point* p, float error);
	void show();

private:
	int x;
	int y;


};

