#include "TurretAFactory.h"


TurretAFactory::TurretAFactory(Game* game)
	: TurretFactory(game) {

}

Turret* TurretAFactory::createTurret() {
	return new TurretA("res/cannon1.png", 0, 0, 55, 14, game);
}