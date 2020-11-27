#include "RoundProjectileFactory.h"

RoundProjectileFactory::RoundProjectileFactory(Game* game)
	: ProjectileFactory(game)
{
}

Projectile* RoundProjectileFactory::createProjectile()
{
	return new RoundProjectile(0, 0, game);
}
