#include "PathManager.h"

PathManager::PathManager() {
	// Tres trayectorias distintas.
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

void PathManager::update(Pawn* pawn) {
	Path* path = paths[pawn->pathId];

	if (path != nullptr && !pawn->stopFollowing) {

		Point* actualPoint = pawn->getActualPoint(); // Posición actual en la matriz.
		if (pawn->nextPoint == nullptr) {
			pawn->vx = -1 * pawn->speed;
			pawn->vy = 0;
		} else if (pawn->isAtDestiny()) { // Pawn a llegado a su destino
			pawn->nextPoint = path->getNextPoint(actualPoint, pawn->lastPoint);
			pawn->lastPoint = new Point(actualPoint->getX(), actualPoint->getY());
		} else {
			pawn->move();
		}
	} else {
		pawn->vx = 0;
		pawn->vy = 0;
	}
}



//void PathManager::update(Actor* actor) {
//	Path* path = paths[actor->pathId];
//
//	if (path != nullptr) { 
//		if (actor->state == Actor::ActorState::MOVING) {
//			Point* actualPoint = actor->getMatrixPoint(); // Posición actual en la matriz.
//
//			if (actor->nextPoint == nullptr) {
//				actor->vx = -1 * actor->speed;
//				actor->vy = 0;
//			}
//			else if (actor->isInPoint(actor->nextPoint)) { // Actor ha llegado al punto siguiente
//				actor->nextPoint = path->getNextPoint(actualPoint, actor->lastPoint);
//				actor->lastPoint = new Point(actualPoint->getX(), actualPoint->getY());
//			}
//			else {
//				int horizontal = (actor->nextPoint->getX() * TILE_WIDTH + TILE_WIDTH/2) - actor->x;
//				int vertical = (actor->nextPoint->getY() * TILE_HEIGHT + TILE_HEIGHT/2) - actor->y;
//
//				if (horizontal < 0) {
//					actor->vx = -1 * actor->speed;
//				}
//
//				if (horizontal > 0) {
//					actor->vx = actor->speed;
//				}
//
//				if (horizontal == 0) {
//					actor->vx = 0;
//				}
//
//				if (vertical < 0) {
//					actor->vy = -1 * actor->speed;
//				}
//
//				if (vertical > 0) {
//					actor->vy = actor->speed;
//				}
//
//				if (vertical == 0) {
//					actor->vy = 0;
//				}
//			}
//		} else {
//			actor->vx = 0;
//			actor->vy = 0;
//		}
//		
//	}
//}