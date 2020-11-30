#include "MissileFactory.h"

MissileFactory::MissileFactory(Game* game)
	: ProjectileFactory(game)
{
}

Projectile* MissileFactory::createProjectile()
{
	return new Missile(0, 0, game);
}
