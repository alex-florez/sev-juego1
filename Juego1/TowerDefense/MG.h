#pragma once

#include "Turret.h"
#include "Game.h"
#include "MGBulletFactory.h"

#define MG_KILLED_ENEMIES_FOR_UPGRADE 4

/// <summary>
/// Clase que representa una ametralladora ligera.
/// </summary>
class MG : public Turret
{
public:
	MG(string filename, float x, float y, float width, float height, int cost, Game* game);

	void upgrade() override;

};

