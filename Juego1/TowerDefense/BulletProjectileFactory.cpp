#include "BulletProjectileFactory.h"

BulletProjectileFactory::BulletProjectileFactory(Game* game)
	: ProjectileFactory(game)
{
}

Projectile* BulletProjectileFactory::createProjectile()
{
	return new BulletProjectile(0, 0, game);
}
