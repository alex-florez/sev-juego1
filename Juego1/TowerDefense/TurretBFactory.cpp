#include "TurretBFactory.h"

TurretBFactory::TurretBFactory(Game* game)
	: TurretFactory(game) {

	this->iconView = new Actor("res/cannon2Icon.png", 0, 0, 31, 44, game);
}


Turret* TurretBFactory::createTurret() {
	return new TurretB("res/cannon2.png", 0, 0, 60, 42, game);
}