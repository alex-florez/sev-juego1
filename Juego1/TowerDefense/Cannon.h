#pragma once

#include "Turret.h"
#include "Game.h"
#include "BulletProjectileFactory.h"

#define CANNON_KILLED_ENEMIES_FOR_UPGRADE 2

/// <summary>
/// Clase que representa un Cañón.
/// </summary>
class Cannon : public Turret
{
public:
	Cannon(string filename, float x, float y, float width, float height, int cost, Game* game);
	
	void upgrade() override;
};

