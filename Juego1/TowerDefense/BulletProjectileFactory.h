#pragma once
#include "ProjectileFactory.h"
#include "Game.h"
#include "Projectile.h"
#include "BulletProjectile.h"

class BulletProjectileFactory : public ProjectileFactory
{
public:
	BulletProjectileFactory(Game* game);
	Projectile* createProjectile() override;
};

