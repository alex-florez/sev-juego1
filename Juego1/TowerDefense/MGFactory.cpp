#include "MGFactory.h"

MGFactory::MGFactory(Game* game)
	: TurretFactory(game) {
}


int MGFactory::getCost() {
	return MG_COST;
}

Actor* MGFactory::getIcon()
{
	return new Actor("res/turrets/mg/MGIcon.png", 0, 0, 44, 21, game);
}

Turret* MGFactory::createTurret() {
	return new MG("res/turrets/mg/MG.png", 0, 0, 44, 21, getCost(), game);
}