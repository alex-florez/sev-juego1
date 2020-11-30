#include "CannonFactory.h"


CannonFactory::CannonFactory(Game* game)
	: TurretFactory(game) {
	
}

int CannonFactory::getCost() {
	return CANNON_COST;
}

Actor* CannonFactory::getIcon() {
	return new Actor("res/turrets/cannon/CannonIcon.png", 0, 0, 44, 24, game);
}

Turret* CannonFactory::createTurret() {
	return new Cannon("res/turrets/cannon/Cannon.png", 0, 0, 44, 24, getCost(), game);
}