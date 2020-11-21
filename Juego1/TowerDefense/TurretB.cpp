#include "TurretB.h"


TurretB::TurretB(string filename, float x, float y, float width, float height, Game* game)
	: Turret(filename, x, y, width, height, game) {

	this->cost = 500;
}