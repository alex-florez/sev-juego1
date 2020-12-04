#include "BulletProjectileFactory.h"

BulletProjectileFactory::BulletProjectileFactory(Game* game)
	: ProjectileFactory(game)
{
	this->hitSound = new SoundEffect("res/sounds/enemyHit.wav");
}

Projectile* BulletProjectileFactory::createProjectile()
{
	Projectile* p = new BulletProjectile(0, 0, game);
	p->hitSound = this->hitSound;
	return p;
}
