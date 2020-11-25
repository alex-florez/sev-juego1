#include "TurretAFactory.h"


TurretAFactory::TurretAFactory(Game* game)
	: TurretFactory(game) {
	
}

int TurretAFactory::getCost() {
	return TURRET_A_COST;
}

Actor* TurretAFactory::getIcon() {
	return new Actor("res/cannon1Icon.png", 0, 0, 43, 11, game);
}

Turret* TurretAFactory::createTurret() {
	return new TurretA("res/cannon1.png", 0, 0, 55, 14, game);
}