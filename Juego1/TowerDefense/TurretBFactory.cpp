#include "TurretBFactory.h"

TurretBFactory::TurretBFactory(Game* game)
	: TurretFactory(game) {
}


int TurretBFactory::getCost() {
	return TURRET_B_COST;
}

Actor* TurretBFactory::getIcon()
{
	return new Actor("res/cannon2Icon.png", 0, 0, 44, 31, game);
}

Turret* TurretBFactory::createTurret() {
	return new TurretB("res/cannon2.png", 0, 0, 60, 42, game);
}