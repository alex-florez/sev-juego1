#include "MGBullet.h"

MGBullet::MGBullet(float x, float y, Game* game)
	: Projectile("res/turrets/mg/Bullet_MG.png", 22, 6, 32, 8, x, y, game)
{
	this->hitSound = nullptr;
}
