#include "Path.h"

Path::Path() {
	init();
}

void Path::addPoint(Point* point) {
	this->pathMatrix[point->getY()][point->getX()] = true;
}


Point* Path::getNextPoint(Point* actual, Point* last) {
	Point* next = nullptr;

	Point* up = new Point(actual->getX(), actual->getY()-1);
	Point* down = new Point(actual->getX(), actual->getY()+1);
	Point* right = new Point(actual->getX()+1, actual->getY());
	Point* left = new Point(actual->getX()-1, actual->getY());

	if (get(up) && (last == nullptr || !last->equals(up, 0))) {
		next = new Point(up->getX(), up->getY());
	}
	else if (get(right) && (last == nullptr || !last->equals(right, 0))) {
		next = new Point(right->getX(), right->getY());
	}
	else if (get(left) && (last == nullptr || !last->equals(left, 0))) {
		next = new Point(left->getX(), left->getY());
	}
	else if (get(down) && (last == nullptr || !last->equals(down, 0))) {
		next = new Point(down->getX(), down->getY());
	}

	return next;
}


void Path::show() {

	cout << "Mostrando camino" << endl;

	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 20; j++) {
			cout << this->pathMatrix[i][j];
		}

		cout << endl;
	}
}


void Path::init() {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 20; j++) {
			this->pathMatrix[i][j] = false;
		}
	}
}

bool Path::get(Point* point) {
	if (point->getX() >= 20 || point->getY() < 0) {
		return false;
	}
	return this->pathMatrix[point->getY()][point->getX()];
}
