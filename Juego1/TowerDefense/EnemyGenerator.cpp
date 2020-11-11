#include "EnemyGenerator.h"

EnemyGenerator::EnemyGenerator(int pathId, int x, int y, Game* game) {
	this->x = x;
	this->y = y;
	this->game = game;
	this->pathId = pathId;
	this->startPoint = new Point(x-1, y);
}


Enemy* EnemyGenerator::createEnemy() {
	Enemy* e = new Enemy(this->x*40+20, this->y*40+20, 2, this->game);
	e->pathId = this->pathId;
	e->nextPoint = this->startPoint;
	return e;
}