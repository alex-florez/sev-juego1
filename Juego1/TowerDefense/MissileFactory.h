#pragma once
#include "ProjectileFactory.h"
#include "Missile.h"

class MissileFactory : public ProjectileFactory
{
public:
	MissileFactory(Game* game);
	Projectile* createProjectile() override;
};

