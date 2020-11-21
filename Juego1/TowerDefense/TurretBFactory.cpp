#include "TurretBFactory.h"

TurretBFactory::TurretBFactory(Game* game)
	: TurretFactory(game) {

	this->iconView = new Actor("res/cannon2Icon.png", 0, 0, 44, 31, game);
	this->iconName = "res/cannon2Icon.png";
	this->iconWidth = 44;
	this->iconHeight = 31;
	this->cost = 500;
}


Turret* TurretBFactory::createTurret() {
	return new TurretB("res/cannon2.png", 0, 0, 60, 42, game);
}