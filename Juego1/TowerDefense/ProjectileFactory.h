#pragma once

#include "Projectile.h"
#include "Game.h"

/// <summary>
/// Clase base para las factorías de proyectiles.
/// </summary>
class ProjectileFactory
{
public:
	ProjectileFactory(Game* game);
	virtual Projectile* createProjectile() = 0;

	Game* game;
};

