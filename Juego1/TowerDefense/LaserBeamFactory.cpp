#include "LaserBeamFactory.h"

LaserBeamFactory::LaserBeamFactory(Game* game)
	: ProjectileFactory(game)
{
}

Projectile* LaserBeamFactory::createProjectile()
{
	return new LaserBeam(0, 0, game);
}
