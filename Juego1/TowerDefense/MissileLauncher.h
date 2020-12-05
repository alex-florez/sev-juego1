#pragma once
#include "Turret.h"
#include "MissileFactory.h"

#define MISSILE_LAUNCHER_KILLED_ENEMIES_FOR_UPGRADE 6

/// <summary>
/// Clase que representa un lanzacohetes.
/// </summary>
class MissileLauncher : public Turret
{
public:
	MissileLauncher(string filename, float x, float y, float width, float height, int cost, Game* game);
	
	void upgrade() override;
};

