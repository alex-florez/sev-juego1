#include "LaserBeam.h"

LaserBeam::LaserBeam(float x, float y, Game* game)
	: Projectile("res/laser_beam1.png", 20, 4, 22, 30, x, y, game)
{
}
