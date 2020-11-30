#pragma once

#include "Turret.h"
#include "Game.h"
#include "BulletProjectileFactory.h"

/// <summary>
/// Clase que representa un Cañón.
/// </summary>
class Cannon : public Turret
{
public:
	Cannon(string filename, float x, float y, float width, float height, int cost, Game* game);

};

