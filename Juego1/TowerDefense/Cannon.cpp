#include "Cannon.h"


Cannon::Cannon(string filename, float x, float y, float width, float height, int cost, Game* game)
	: Turret(filename, x, y, width, height, cost, game) {

	this->projectileFactory = new BulletProjectileFactory(game);
	// Caracter�sticas de la torreta
	this->shootCadency = 30;
	this->xDetectionRange = 3;
	this->yDetectionRange = 3;
}