#include "MGBulletFactory.h"

MGBulletFactory::MGBulletFactory(Game* game)
	: ProjectileFactory(game)
{
	this->hitSound = new SoundEffect("res/sounds/enemyHit.wav");
}

Projectile* MGBulletFactory::createProjectile()
{
	Projectile* p = new MGBullet(0, 0, game);
	p->hitSound = this->hitSound;
	return p;
}
