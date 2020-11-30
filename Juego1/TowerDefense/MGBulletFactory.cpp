#include "MGBulletFactory.h"

MGBulletFactory::MGBulletFactory(Game* game)
	: ProjectileFactory(game)
{
}

Projectile* MGBulletFactory::createProjectile()
{
	return new MGBullet(0, 0, game);
}
