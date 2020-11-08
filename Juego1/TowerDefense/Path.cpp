#include "Path.h"

Path::Path() {
	init();
}

void Path::addPoint(int i, int j) {
	this->pathMatrix[i][j] = 1;
}


Point* Path::getNextPoint(Point* actual, Point* last) {
	Point* next = nullptr;

	Point* up = new Point(actual->getX(), actual->getY()-1);
	Point* down = new Point(actual->getX(), actual->getY()+1);
	Point* right = new Point(actual->getX()+1, actual->getY());
	Point* left = new Point(actual->getX()-1, actual->getY());

	if (get(up) > 0 && (last == nullptr || !last->equals(up, 0))) {
		next = new Point(up->getX(), up->getY());
	}
	else if (get(right) > 0 && (last == nullptr || !last->equals(right, 0))) {
		next = new Point(right->getX(), right->getY());
	}
	else if (get(left) > 0 && (last == nullptr || !last->equals(left, 0))) {
		next = new Point(left->getX(), left->getY());
	}
	else if (get(down) > 0 && (last == nullptr || !last->equals(down, 0))) {
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
			this->pathMatrix[i][j] = 0;
		}
	}
}

int Path::get(Point* point) {
	if (point->getX() >= 20 || point->getY() < 0) {
		return -1;
	}
	return this->pathMatrix[point->getY()][point->getX()];
}
