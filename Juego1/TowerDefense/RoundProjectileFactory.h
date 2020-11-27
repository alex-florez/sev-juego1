#pragma once
#include "ProjectileFactory.h"
#include "Game.h"
#include "Projectile.h"
#include "RoundProjectile.h"

class RoundProjectileFactory : public ProjectileFactory
{
public:
	RoundProjectileFactory(Game* game);
	Projectile* createProjectile() override;
};

