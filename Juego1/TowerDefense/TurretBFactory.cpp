#include "TurretBFactory.h"

TurretBFactory::TurretBFactory(Game* game)
	: TurretFactory(game) {

}


Turret* TurretBFactory::createTurret() {
	return new TurretB("res/cannon2.png", 0, 0, 47, 25, game);
}