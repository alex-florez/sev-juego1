#pragma once
#include "ProjectileFactory.h"
#include "Game.h"
#include "Projectile.h"
#include "LaserBeam.h"

class LaserBeamFactory : public ProjectileFactory
{
public:
	LaserBeamFactory(Game* game);
	Projectile* createProjectile() override;
};

