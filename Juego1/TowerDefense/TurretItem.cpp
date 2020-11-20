#include "TurretItem.h"


TurretItem::TurretItem(string filename, TurretFactory* turretFactory, float x, float y, Game* game)
	: Actor(filename, x, y, 50, 50, game) {

	this->turretFactory = turretFactory;
}