#pragma once
#include "Turret.h"
#include "MissileFactory.h"

/// <summary>
/// Clase que representa un lanzacohetes.
/// </summary>
class MissileLauncher : public Turret
{
public:
	MissileLauncher(string filename, float x, float y, float width, float height, int cost, Game* game);
};

