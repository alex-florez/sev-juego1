#include "Missile.h"

Missile::Missile(float x, float y, Game* game)
	: Projectile("res/turrets/missileLauncher/Missile.png", 23, 13, 14, 55, x, y, game)
{
}
