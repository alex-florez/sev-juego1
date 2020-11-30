#include "BulletProjectile.h"

BulletProjectile::BulletProjectile(float x, float, Game* game)
	: Projectile("res/turrets/cannon/Bullet_Cannon.png", 16, 8, 20, 20, x, y, game)
{
}
