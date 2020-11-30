#pragma once
#include "ProjectileFactory.h"
#include "Game.h"
#include "Projectile.h"
#include "MGBullet.h"

class MGBulletFactory : public ProjectileFactory
{
public:
	MGBulletFactory(Game* game);
	Projectile* createProjectile() override;
};

