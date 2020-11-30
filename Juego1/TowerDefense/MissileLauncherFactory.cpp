#include "MissileLauncherFactory.h"

MissileLauncherFactory::MissileLauncherFactory(Game* game)
	: TurretFactory(game)
{
}

int MissileLauncherFactory::getCost()
{
	return MISSILE_LAUNCHER_COST;
}

Actor* MissileLauncherFactory::getIcon()
{
	return new Actor("res/turrets/missileLauncher/MissileLauncherIcon.png", 0, 0, 44, 27, game);
}

Turret* MissileLauncherFactory::createTurret()
{
	return new MissileLauncher("res/turrets/missileLauncher/MissileLauncher.png", 0, 0, 44, 27, getCost(), game);
}
