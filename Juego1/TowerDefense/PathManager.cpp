#include "PathManager.h"

PathManager::PathManager() {
	paths[1] = new Path();
	paths[2] = new Path();
	paths[3] = new Path();
}


void PathManager::addPath(int id, Path* path) {
	if (paths.find(id) == paths.end()) { // Si no existe una trayectoria con ese id...
		paths[id] = path;
	}
}


Path* PathManager::getPath(int id) {
	return paths[id];
}

void PathManager::addPointToPath(int pathId, Point* point) {
	Path* path = paths[pathId];
	if (path != nullptr) {
		path->addPoint(point);
	}
}

void PathManager::update(Actor* actor) {
	Path* path = paths[actor->pathId];

	if (path != nullptr) { 
		Point* actualPoint = actor->getMatrixPoint(); // Posici�n actual en la matriz.

		if (actor->nextPoint == nullptr) {
			actor->vx = -2;
			actor->vy = 0;
		}
		else {
			/*if (actor->nextPoint->equals(actualPoint, 0)) {*/ // El actor a llegado al siguiente punto.
			if(actor->isInPoint(actor->nextPoint)){
				actor->nextPoint = path->getNextPoint(actualPoint, actor->lastPoint);
				actor->lastPoint = new Point(actualPoint->getX(), actualPoint->getY());
			}
			else {
				//int horizontal = actor->nextPoint->getX() - actualPoint->getX();
				//int vertical = actor->nextPoint->getY() - actualPoint->getY();

				int horizontal = (actor->nextPoint->getX() * 40 + 20) - actor->x;
				int vertical = (actor->nextPoint->getY() * 40 + 20) - actor->y;

				if (horizontal < 0) {
					actor->vx = -1 * 2;
				}

				if (horizontal > 0) {
					actor->vx = 2;
				}

				if (horizontal == 0) {
					actor->vx = 0;
				}

				if (vertical < 0) {
					actor->vy = -1 * 2;
				}

				if (vertical > 0) {
					actor->vy = 2;
				}

				if (vertical == 0) {
					actor->vy = 0;
				}
			}
		}
	}
}