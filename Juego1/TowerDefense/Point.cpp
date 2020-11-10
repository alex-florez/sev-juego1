#include "Point.h"

Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}

int Point::getX() {
	return this->x;
}

int Point::getY() {
	return this->y;
}

bool Point::equals(Point* p, float error) {
	int otherX = p->getX() * 40 + 20;
	int otherY = p->getY() * 40 + 20;
	
	int thisX = this->x * 40 + 20;
	int thisY = this->y * 40 + 20;

	return thisX == otherX && thisY == otherY;
}

//bool Point::equals(Point* p, float error) {
//	int left = this->x - error;
//	int right = this->x + error;
//	int up = this->y - error;
//	int down = this->y + error;
//
//	return p->getX() >= left && p->getX() <= right && p->getY() >= up && p->getY() <= down;
//}

void Point::show() {
	cout << "{x: " << this->x << " y: " << this->y << "}" << endl;
}